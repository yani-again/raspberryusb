#include <stdint.h>
#include "raspberryusb_drivers.h"
#include "raspberryusb_globals.h"


void rusb_isr(void)
{
    // packet received
    /**
     * NOTE! this ISR only notifies whether or not a packet has been transferred, it does
     *       NOT specify which endpoint/direction it's for. It's the programmer's job to
     *       ensure they're checking for this in their code.
     */
    if (RUSB_INTS & (RUSB_INTS_BUFF_STATUS | RUSB_INTS_TRANS_COMPLETE))
    {
        for (uint8_t i = 0; i < 16; ++i)
        {
            if (RUSB_BUFF_STATUS & RUSB_BUFF_STATUS_EP_OUT(i))
            {
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

                // NOTE! leave this line last
                RUSB_BUFF_STATUS = 0;

                return;
            }

            /**
             * separate `if` checks increases memory footprint but decrease checks per
             * transfer, should be faster overall
             */
            if (RUSB_BUFF_STATUS & RUSB_BUFF_STATUS_EP_IN(i))
            {
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
        return;
    }
}

void rusb_reset(void)
{
    RUSB_MAIN_CTRL |= RUSB_MAIN_CTRL_CONTROLLER_EN;
    RUSB_INTE |= RUSB_INTE_BUS_RESET;
    RUSB_SIE_CTRL |= RUSB_SIE_CTRL_DIRECT_DP;   // signal full-speed
}

