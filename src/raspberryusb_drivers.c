#include <stdint.h>
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
                        global_packet_response_out = Stall;
                        global_buffer_status[0][i] = 1;
                        RUSB_BUFF_STATUS = 0;

                        return;
                    }
                }

                if (RUSB_INTS & RUSB_INTS_BUFF_STATUS)
                {
                    global_packet_response_out = Trans_done;
                }
                else
                {
                    global_packet_response_out = Trans_complete;
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
                        global_packet_response_in = Stall;
                        global_buffer_status[1][i] = 1;
                        RUSB_BUFF_STATUS = 0;

                        return;
                    }
                }

                if (RUSB_INTS & RUSB_INTS_BUFF_STATUS)
                {
                    global_packet_response_in = Trans_done;
                }
                else
                {
                    global_packet_response_in = Trans_complete;
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
                global_packet_response_out = Trans_done;

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
        global_USB_state = Default;
        global_packet_response_out = None;

        return;
    }

    if (RUSB_INTS & RUSB_INTS_DEV_RESUME_FROM_HOST)
    {
        RUSB_SIE_STATUS &= ~RUSB_SIE_STATUS_SUSPENDED;
        global_USB_state = Configured;

        return;
    }

    if (RUSB_INTS & RUSB_INTS_DEV_SUSPEND)
    {
        global_USB_state = Suspended;

        return;
    }

    if (RUSB_INTS & RUSB_INTS_DEV_CONN_DIS)
    {
        global_USB_state = None;

        return;
    }

    // TODO: implement error handling
    if (RUSB_INTS & (RUSB_INTS_ERROR_CRC
                   | RUSB_INTS_ERROR_BIT_STUFF
                   | RUSB_INTS_ERROR_RX_OVERFLOW
                   | RUSB_INTS_ERROR_RX_TIMEOUT
                   | RUSB_INTS_DATA_SEQ))
    {
        RUSB_INTS &= ~(RUSB_INTS_ERROR_CRC
                     | RUSB_INTS_ERROR_BIT_STUFF
                     | RUSB_INTS_ERROR_RX_OVERFLOW
                     | RUSB_INTS_ERROR_RX_TIMEOUT
                     | RUSB_INTS_DATA_SEQ);

        return;
    }

    // TODO: finish when able to send/receive data
    if (RUSB_INTS & RUSB_INTS_SETUP_REQ)
    {
        global_USB_state = Default;
        return;
    }
}

void rusb_reset(void)
{
    RUSB_MAIN_CTRL |= RUSB_MAIN_CTRL_CONTROLLER_EN;
    RUSB_INTE |= RUSB_INTE_BUS_RESET;
    RUSB_SIE_CTRL |= RUSB_SIE_CTRL_DIRECT_DP;   // signal full-speed
}

uint16_t rusb_handle_out_packet(void)
{
    if (global_packet_response_out != None)
    {
        global_packet_response_out = None;

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
        case Trans:
            RUSB_DPSRAM_EP_IN_BUFF_CTRL(ep_num) |= RUSB_EP_BUFF_CTRL_BUFF0_FULL;
            // make buffer unavailable
            RUSB_DPSRAM_EP_IN_BUFF_CTRL(ep_num) &= ~RUSB_EP_BUFF_CTRL_BUFF0_AVAILABLE;

            RUSB_DPSRAM_EP_IN_CTRL(ep_num);

            break;
        case Stall:
            global_packet_response_in = Stall;
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
 *        macros RUSB_EP_TYPE_<type> where <type> is one of:
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
        case RUSB_EP_TYPE_CONTROL:
            RUSB_DPSRAM_EP_OUT_CTRL(ep_num) |= RUSB_EP_CTRL_TYPE_CONTROL;
            break;
        case RUSB_EP_TYPE_ISOCHRONOUS:
            RUSB_DPSRAM_EP_OUT_CTRL(ep_num) |= RUSB_EP_CTRL_TYPE_ISO;
            break;
        case RUSB_EP_TYPE_INTERRUPT:
            RUSB_DPSRAM_EP_OUT_CTRL(ep_num) |= RUSB_EP_CTRL_TYPE_INTERRUPT;
            break;
        case RUSB_EP_TYPE_BULK:
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
 *        macros RUSB_EP_TYPE_<type> where <type> is one of:
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
        case RUSB_EP_TYPE_CONTROL:
            RUSB_DPSRAM_EP_IN_CTRL(ep_num) |= RUSB_EP_CTRL_TYPE_CONTROL;
            break;
        case RUSB_EP_TYPE_ISOCHRONOUS:
            RUSB_DPSRAM_EP_IN_CTRL(ep_num) |= RUSB_EP_CTRL_TYPE_ISO;
            break;
        case RUSB_EP_TYPE_INTERRUPT:
            RUSB_DPSRAM_EP_IN_CTRL(ep_num) |= RUSB_EP_CTRL_TYPE_INTERRUPT;
            break;
        case RUSB_EP_TYPE_BULK:
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
