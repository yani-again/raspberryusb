#include <stdint.h>
#include <string.h>
#include "raspberryusb_drivers.h"
#include "raspberryusb_usb.h"
#include "raspberryusb_globals.h"


void rusb_isr(void)
{
    // packet received
    if (RUSB_INTS & (RUSB_INTS_BUFF_STATUS | RUSB_INTS_TRANS_COMPLETE))
    {
        for (uint8_t i = 0; i < 16; ++i)
        {
            if (RUSB_BUFF_STATUS & RUSB_BUFF_STATUS_EP_OUT(i))
            {
                // check for STALL
                if (RUSB_DPSRAM_EP_OUT_BUFF_CTRL(i) & RUSB_EP_BUFF_CTRL_BUFF0_SEND_STALL)
                {
                    if ((i != 0) ||
                            (i == 0 && (RUSB_EP_STALL_ARM & RUSB_EP_STALL_ARM_EP0_OUT)))
                    {
                        global_packet_response_out = Out_Stall;
                        global_buffer_status[0][i] = 1;
                        RUSB_BUFF_STATUS = 0;

                        return;
                    }
                }

                if (RUSB_INTS & RUSB_INTS_BUFF_STATUS)
                {
                    global_packet_response_out = Out_Trans_done;
                }
                else
                {
                    global_packet_response_out = Out_Trans_complete;
                    /* TODO: datasheet says this bit is RO but it also says "clear by
                     * writing to this bit" - figure out which it is */
                    RUSB_INTS &= ~RUSB_INTS_TRANS_COMPLETE;
                }

                global_buffer_status[0][i] = 1;

                // NOTE! leave this line last
                RUSB_BUFF_STATUS = 0;

                return;
            }

            /**
             * separate `if` checks increases memory footprint but decrease checks per
             * transfer, speed is likely more important in most cases
             */
            if (RUSB_BUFF_STATUS & RUSB_BUFF_STATUS_EP_IN(i))
            {
                // check for STALL
                if (RUSB_DPSRAM_EP_IN_BUFF_CTRL(i) & RUSB_EP_BUFF_CTRL_BUFF0_SEND_STALL)
                {
                    if ((i != 0) ||
                            (i == 0 && (RUSB_EP_STALL_ARM & RUSB_EP_STALL_ARM_EP0_IN)))
                    {
                        global_packet_response_in = In_Stall;
                        global_buffer_status[1][i] = 1;
                        RUSB_BUFF_STATUS = 0;

                        return;
                    }
                }

                if (RUSB_INTS & RUSB_INTS_BUFF_STATUS)
                {
                    global_packet_response_in = In_Trans;
                }
                else
                {
                    global_packet_response_in = In_Trans_done;
                    /* TODO: datasheet says this bit is RO but it also says "clear by
                     * writing to this bit" - figure out which it is */
                    RUSB_INTS &= ~RUSB_INTS_TRANS_COMPLETE;
                }

                global_buffer_status[1][i] = 1;

                // NOTE! leave this line last
                RUSB_BUFF_STATUS = 0;

                return;
            }
        }

        return;
    }

    if (RUSB_INTS & RUSB_INTS_BUFF_STATUS)
    {
        for (uint8_t i = 0; i < 16; ++i)
        {
            if (RUSB_BUFF_STATUS & RUSB_BUFF_STATUS_EP_OUT(i))
            {
                global_packet_response_out = Out_Trans_done;

                // NOTE! ensure this line is last
                RUSB_BUFF_STATUS = 0;

                return;
            }
        }

        return;
    }

    if (RUSB_INTS & RUSB_INTS_BUS_RESET)
    {
        RUSB_INTS = 0;
        RUSB_SIE_STATUS = 0;    // reset in case left-over bits
        RUSB_ADDR_ENDP &= 0xFF80;   // zero out address
        RUSB_MAIN_CTRL |= RUSB_MAIN_CTRL_CONTROLLER_EN;
        RUSB_MAIN_CTRL &= ~RUSB_MAIN_CTRL_HOST_NDEVICE;
        RUSB_SIE_CTRL |= RUSB_SIE_CTRL_EP0_INT_1BUFF
                       | RUSB_SIE_CTRL_RESUME;
        RUSB_INTE |= RUSB_INTE_SETUP_REQ
                   | RUSB_INTE_DEV_RESUME_FROM_HOST
                   | RUSB_INTE_DEV_SUSPEND
                   | RUSB_INTE_TRANS_COMPLETE;
        global_USB_state = State_Default;
        global_packet_response_out = Out_None;

        return;
    }

    if (RUSB_INTS & RUSB_INTS_DEV_RESUME_FROM_HOST)
    {
        RUSB_SIE_STATUS &= ~RUSB_SIE_STATUS_SUSPENDED;
        global_USB_state = State_Configured;

        return;
    }

    if (RUSB_INTS & RUSB_INTS_DEV_SUSPEND)
    {
        global_USB_state = State_Suspended;

        return;
    }

    if (RUSB_INTS & RUSB_INTS_DEV_CONN_DIS)
    {
        global_USB_state = State_None;

        return;
    }

    // TODO: implement error handling
    if (RUSB_INTS & (RUSB_INTS_ERROR_CRC
                   | RUSB_INTS_ERROR_BIT_STUFF
                   | RUSB_INTS_ERROR_RX_OVERFLOW
                   | RUSB_INTS_ERROR_RX_TIMEOUT
                   | RUSB_INTS_ERROR_DATA_SEQ))
    {
        RUSB_INTS &= ~(RUSB_INTS_ERROR_CRC
                     | RUSB_INTS_ERROR_BIT_STUFF
                     | RUSB_INTS_ERROR_RX_OVERFLOW
                     | RUSB_INTS_ERROR_RX_TIMEOUT
                     | RUSB_INTS_ERROR_DATA_SEQ);

        return;
    }

    if (RUSB_INTS & RUSB_INTS_SETUP_REQ)
    {
        // global_USB_state = State_Default;
        // send device descriptor through
        // rusb_packet_response_in setup_response = In_Trans;
        // rusb_handle_in_packet(0, setup_response);

        uint8_t bRequest = (RUSB_DPSRAM_SETUP_PACKET)[1];

        if (bRequest == GET_DESCRIPTOR)
        {
            uint8_t wDescriptorType = (RUSB_DPSRAM_SETUP_PACKET)[3];
            uint8_t wDescriptorIndex = (RUSB_DPSRAM_SETUP_PACKET)[2];
            uint16_t wLength =
                (((uint16_t) (RUSB_DPSRAM_SETUP_PACKET)[7]) << 8) | 
                (((uint16_t) (RUSB_DPSRAM_SETUP_PACKET)[8]) & 0x00FF);

            /* ensure descriptor is supported by RaspberryUSB.
             * For full list of supported descriptors, see specification.
             */
            uint8_t supported_descriptor = 0;
            for (uint8_t i = 0; rusb_supported_descriptors_count; ++i)
            {
                if (wDescriptorType == rusb_supported_descriptors[i])
                {
                    supported_descriptor = 1;
                    break;
                }
            }

            if (!supported_descriptor)
                return;

            // load the right descriptor in
            rusb_load_descriptor(wDescriptorType, wDescriptorIndex, wLength);

            // send descriptor to host
            rusb_packet_response_in setup_response = In_Trans;
            rusb_handle_in_packet(0, setup_response);
        }
    }
}

void rusb_reset(void)
{
    RUSB_INTE |= RUSB_INTE_BUS_RESET;
    RUSB_SIE_CTRL |= RUSB_SIE_CTRL_DIRECT_DP;   // signal full-speed
}

void rusb_enable_usb(void)
{
    RUSB_MAIN_CTRL |= RUSB_MAIN_CTRL_CONTROLLER_EN;
}

void rusb_load_descriptor(uint8_t wDescriptorType, uint8_t wDescriptorIndex, uint16_t wLength)
{
    // zero-out data buffer first to remove previous data
    memset(RUSB_IN_EP0_BUFFER0, 0, 0x40);

    switch (wDescriptorType)
    {
        case 0x01:
            RUSB_IN_EP0_BUFFER0[0] = device_descriptor.bLength;
            RUSB_IN_EP0_BUFFER0[1] = device_descriptor.bDescriptorType;
            RUSB_IN_EP0_BUFFER0[2] =
                (uint8_t) (device_descriptor.bcdUSB & 0xFF);
            RUSB_IN_EP0_BUFFER0[3] = 
                (uint8_t) ((device_descriptor.bcdUSB >> 8) & 0xFF);
            RUSB_IN_EP0_BUFFER0[4] = device_descriptor.bDeviceClass;
            RUSB_IN_EP0_BUFFER0[5] = device_descriptor.bDeviceSubClass;
            RUSB_IN_EP0_BUFFER0[6] = device_descriptor.bDeviceProtocol;
            RUSB_IN_EP0_BUFFER0[7] = device_descriptor.bMaxPacketSize0;
            RUSB_IN_EP0_BUFFER0[8] =
                (uint8_t) (device_descriptor.idVendor & 0xFF);
            RUSB_IN_EP0_BUFFER0[9] =
                (uint8_t) ((device_descriptor.idVendor >> 8) & 0xFF);
            RUSB_IN_EP0_BUFFER0[10] =
                (uint8_t) (device_descriptor.idProduct & 0xFF);
            RUSB_IN_EP0_BUFFER0[11] =
                (uint8_t) ((device_descriptor.idProduct >> 8) & 0xFF);
            RUSB_IN_EP0_BUFFER0[12] =
                (uint8_t) (device_descriptor.bcdDevice & 0xFF);
            RUSB_IN_EP0_BUFFER0[13] =
                (uint8_t) ((device_descriptor.bcdDevice >> 8) & 0xFF);
            RUSB_IN_EP0_BUFFER0[14] = device_descriptor.iManufacturer;
            RUSB_IN_EP0_BUFFER0[15] = device_descriptor.iProduct;
            RUSB_IN_EP0_BUFFER0[16] = device_descriptor.iSerialNumber;
            RUSB_IN_EP0_BUFFER0[17] = device_descriptor.bNumConfigurations;
            break;
        case 0x02:
            if (wLength != configuration_descriptor.wTotalLength)
            {
                RUSB_IN_EP0_BUFFER0[0] = configuration_descriptor.bLength;
                RUSB_IN_EP0_BUFFER0[1] = configuration_descriptor.bDescriptorType;
                RUSB_IN_EP0_BUFFER0[2] =
                    (uint8_t) (configuration_descriptor.wTotalLength & 0xFF);
                RUSB_IN_EP0_BUFFER0[3] =
                    (uint8_t) ((configuration_descriptor.wTotalLength >> 8) & 0xFF);
                RUSB_IN_EP0_BUFFER0[4] = configuration_descriptor.bNumInterfaces;
                RUSB_IN_EP0_BUFFER0[5] = configuration_descriptor.bConfigurationValue;
                RUSB_IN_EP0_BUFFER0[6] = configuration_descriptor.iConfiguration;
                RUSB_IN_EP0_BUFFER0[7] = configuration_descriptor.bmAttributes;
                RUSB_IN_EP0_BUFFER0[8] = configuration_descriptor.MaxPower;
            }
            else
            {
                RUSB_IN_EP0_BUFFER0[0] = configuration_descriptor.bLength;
                RUSB_IN_EP0_BUFFER0[1] = configuration_descriptor.bDescriptorType;
                RUSB_IN_EP0_BUFFER0[2] =
                    (uint8_t) (configuration_descriptor.wTotalLength & 0xFF);
                RUSB_IN_EP0_BUFFER0[3] =
                    (uint8_t) ((configuration_descriptor.wTotalLength >> 8) & 0xFF);
                RUSB_IN_EP0_BUFFER0[4] = configuration_descriptor.bNumInterfaces;
                RUSB_IN_EP0_BUFFER0[5] = configuration_descriptor.bConfigurationValue;
                RUSB_IN_EP0_BUFFER0[6] = configuration_descriptor.iConfiguration;
                RUSB_IN_EP0_BUFFER0[7] = configuration_descriptor.bmAttributes;
                RUSB_IN_EP0_BUFFER0[8] = configuration_descriptor.MaxPower;

                RUSB_IN_EP0_BUFFER0[9] = interface_descriptor.bLength;
                RUSB_IN_EP0_BUFFER0[10] = interface_descriptor.bDescriptorType;
                RUSB_IN_EP0_BUFFER0[11] = interface_descriptor.bInterfaceNumber;
                RUSB_IN_EP0_BUFFER0[12] = interface_descriptor.bAlternateSetting;
                RUSB_IN_EP0_BUFFER0[13] = interface_descriptor.bNumEndpoints;
                RUSB_IN_EP0_BUFFER0[14] = interface_descriptor.bInterfaceClass;
                RUSB_IN_EP0_BUFFER0[15] = interface_descriptor.bInterfaceSubClass;
                RUSB_IN_EP0_BUFFER0[16] = interface_descriptor.bInterfaceProtocol;
                RUSB_IN_EP0_BUFFER0[17] = interface_descriptor.iInterface;

                RUSB_IN_EP0_BUFFER0[18] = endpoint_descriptor_1_in.bLength;
                RUSB_IN_EP0_BUFFER0[19] = endpoint_descriptor_1_in.bDescriptorType;
                RUSB_IN_EP0_BUFFER0[20] = endpoint_descriptor_1_in.bEndpointAddress;
                RUSB_IN_EP0_BUFFER0[21] = endpoint_descriptor_1_in.bmAttributes;
                RUSB_IN_EP0_BUFFER0[22] =
                    (uint8_t) (endpoint_descriptor_1_in.wMaxPacketSize & 0xFF);
                RUSB_IN_EP0_BUFFER0[23] =
                    (uint8_t) ((endpoint_descriptor_1_in.wMaxPacketSize >> 8) & 0xFF);
                RUSB_IN_EP0_BUFFER0[24] = endpoint_descriptor_1_in.bInterval;

                RUSB_IN_EP0_BUFFER0[25] = endpoint_descriptor_1_out.bLength;
                RUSB_IN_EP0_BUFFER0[26] = endpoint_descriptor_1_out.bDescriptorType;
                RUSB_IN_EP0_BUFFER0[27] = endpoint_descriptor_1_out.bEndpointAddress;
                RUSB_IN_EP0_BUFFER0[28] = endpoint_descriptor_1_out.bmAttributes;
                RUSB_IN_EP0_BUFFER0[29] =
                    (uint8_t) (endpoint_descriptor_1_out.wMaxPacketSize & 0xFF);
                RUSB_IN_EP0_BUFFER0[30] =
                    (uint8_t) ((endpoint_descriptor_1_out.wMaxPacketSize >> 8) & 0xFF);
                RUSB_IN_EP0_BUFFER0[31] = endpoint_descriptor_1_out.bInterval;

                RUSB_IN_EP0_BUFFER0[32] = hid_descriptor.bLength;
                RUSB_IN_EP0_BUFFER0[33] = hid_descriptor.bDescriptorType;
                RUSB_IN_EP0_BUFFER0[34] =
                    (uint8_t) (hid_descriptor.bcdHID & 0xFF);
                RUSB_IN_EP0_BUFFER0[35] =
                    (uint8_t) ((hid_descriptor.bcdHID >> 8) & 0xFF);
                RUSB_IN_EP0_BUFFER0[36] = hid_descriptor.bCountryCode;
                RUSB_IN_EP0_BUFFER0[37] = hid_descriptor.bNumDescriptors;
                RUSB_IN_EP0_BUFFER0[38] = hid_descriptor.bDescriptorType;
                RUSB_IN_EP0_BUFFER0[39] =
                    (uint8_t) (hid_descriptor.wDescriptorLength & 0xFF);
                RUSB_IN_EP0_BUFFER0[40] =
                    (uint8_t) ((hid_descriptor.wDescriptorLength >> 8) & 0xFF);
            }
            break;
        case 0x03:
            if (wDescriptorIndex == 1)
            {
                for (uint8_t i = 0;
                     i < sizeof(rusb_string_descriptor_manufacturer);
                     ++i)
                {
                    RUSB_IN_EP0_BUFFER0[i] = rusb_string_descriptor_manufacturer[i];
                }
            }
            else if (wDescriptorIndex == 2)
            {
                for (uint8_t i = 0;
                     i < sizeof(rusb_string_descriptor_product);
                     ++i)
                {
                    RUSB_IN_EP0_BUFFER0[i] = rusb_string_descriptor_product[i];
                }
            }
            else
            {
                for (uint8_t i = 0;
                     i < sizeof(rusb_string_descriptor_serial_number);
                     ++i)
                {
                    RUSB_IN_EP0_BUFFER0[i] = rusb_string_descriptor_serial_number[i];
                }
            }
            break;
        case 0x22:
            for (uint8_t i = 0; i < hid_descriptor.wDescriptorLength; ++i)
                RUSB_IN_EP0_BUFFER0[i] = rusb_report_descriptor[i];
            break;
    }

    return;
}

uint16_t rusb_handle_out_packet(void)
{
    if (global_packet_response_out != Out_None)
    {
        global_packet_response_out = Out_None;

        // TODO: return buffer offset
        for (uint8_t i = 0; i < 16; ++i)
        {
            if (global_buffer_status[0][i])
            {
                // wait for buffer to fill before returning
                while (!(RUSB_DPSRAM_EP_OUT_BUFF_CTRL(i) & RUSB_EP_BUFF_CTRL_BUFF0_FULL))
                    ;
                RUSB_DPSRAM_EP_OUT_BUFF_CTRL(i) &= ~RUSB_EP_BUFF_CTRL_BUFF0_FULL;
                RUSB_DPSRAM_EP_OUT_BUFF_CTRL(i) |= RUSB_EP_BUFF_CTRL_BUFF0_AVAILABLE;

                if (i != 0)
                    return RUSB_EP_OUT_DATA_BUFFER(i);
                return RUSB_IN_EP0_BUFFER0;
            }
        }
    }

    return 0;
}

// TODO: implement 'last buffer' bit setting for end-of-transfer
void rusb_handle_in_packet(uint8_t ep_num, rusb_packet_response_in to_send)
{
    switch (to_send)
    {
        case In_Trans:
            RUSB_DPSRAM_EP_IN_BUFF_CTRL(ep_num) |= RUSB_EP_BUFF_CTRL_BUFF0_FULL;

            // wait some clock cycles - mentioned in RP2040 datasheet
            for (uint8_t i = 0; i < 20; ++i)
                ;

            // make buffer unavailable
            RUSB_DPSRAM_EP_IN_BUFF_CTRL(ep_num) &= ~RUSB_EP_BUFF_CTRL_BUFF0_AVAILABLE;

            break;
        case In_Stall:
            global_packet_response_in = In_Stall;
            RUSB_DPSRAM_EP_IN_BUFF_CTRL(ep_num) |= RUSB_EP_BUFF_CTRL_BUFF0_SEND_STALL;

            break;
        default:
            break;
    }

    return;
}

/**
 * @brief Sets up an OUT endpoint with some default values. See the specification for the
 *        default values.
 *
 * @param `ep_num` is the endpoint number, `ep_type` is the endpoint type - this uses the
 *        macros RUSB_EP_CTRL_TYPE_<type> where <type> is one of:
 *          - CONTROL
 *          - ISOCHRONOUS
 *          - INTERRUPT
 *          - BULK
 */
void rusb_setup_out_endpoint(uint8_t ep_num, uint8_t ep_type)
{
    RUSB_DPSRAM_EP_OUT_CTRL(ep_num) = RUSB_EP_CTRL_INT_TRANS
                                    | RUSB_EP_CTRL_INT_STALL;

    switch (ep_type)
    {
        case RUSB_EP_CTRL_TYPE_CONTROL:
            RUSB_DPSRAM_EP_OUT_CTRL(ep_num) |= RUSB_EP_CTRL_TYPE_CONTROL;
            break;
        case RUSB_EP_CTRL_TYPE_ISOCHRONOUS:
            RUSB_DPSRAM_EP_OUT_CTRL(ep_num) |= RUSB_EP_CTRL_TYPE_ISO;
            break;
        case RUSB_EP_CTRL_TYPE_INTERRUPT:
            RUSB_DPSRAM_EP_OUT_CTRL(ep_num) |= RUSB_EP_CTRL_TYPE_INTERRUPT;
            break;
        case RUSB_EP_CTRL_TYPE_BULK:
            RUSB_DPSRAM_EP_OUT_CTRL(ep_num) |= RUSB_EP_CTRL_TYPE_BULK;
            break;
    }

    // EP0 has that special buffer
    if (ep_num != 0)
        RUSB_DPSRAM_EP_OUT_CTRL(ep_num) |= RUSB_DPSRAM_EP_OUT_BUFF_OFFSET(ep_num);

    // enable once everything is set up
    RUSB_DPSRAM_EP_OUT_CTRL(ep_num) |= RUSB_EP_CTRL_ENABLE;

    return;
}

/**
 * @brief Sets up an IN endpoint with some default values. See the specification for the
 *        default values.
 *
 * @param `ep_num` is the endpoint number, `ep_type` is the endpoint type - this uses the
 *        macros RUSB_EP_CTRL_TYPE_<type> where <type> is one of:
 *          - CONTROL
 *          - ISOCHRONOUS
 *          - INTERRUPT
 *          - BULK
 */
void rusb_setup_in_endpoint(uint8_t ep_num, uint8_t ep_type)
{
    RUSB_DPSRAM_EP_IN_CTRL(ep_num) = RUSB_EP_CTRL_INT_TRANS
                                   | RUSB_EP_CTRL_INT_NAK;

    switch (ep_type)
    {
        case RUSB_EP_CTRL_TYPE_CONTROL:
            RUSB_DPSRAM_EP_IN_CTRL(ep_num) |= RUSB_EP_CTRL_TYPE_CONTROL;
            break;
        case RUSB_EP_CTRL_TYPE_ISOCHRONOUS:
            RUSB_DPSRAM_EP_IN_CTRL(ep_num) |= RUSB_EP_CTRL_TYPE_ISO;
            break;
        case RUSB_EP_CTRL_TYPE_INTERRUPT:
            RUSB_DPSRAM_EP_IN_CTRL(ep_num) |= RUSB_EP_CTRL_TYPE_INTERRUPT;
            break;
        case RUSB_EP_CTRL_TYPE_BULK:
            RUSB_DPSRAM_EP_IN_CTRL(ep_num) |= RUSB_EP_CTRL_TYPE_BULK;
            break;
    }

    // EP0 has that special buffer
    if (ep_num != 0)
        RUSB_DPSRAM_EP_IN_CTRL(ep_num) |= RUSB_DPSRAM_EP_IN_BUFF_OFFSET(ep_num);

    // enable once everything is set up
    RUSB_DPSRAM_EP_IN_CTRL(ep_num) |= RUSB_EP_CTRL_ENABLE;

    return;
}
