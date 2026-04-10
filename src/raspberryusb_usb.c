#include <stdint.h>
#include "raspberryusb_usb.h"
#include "raspberryusb_drivers.h"
#include "raspberryusb_globals.h"


/**
 * @brief Handles IN packets for a specific endpoint, setting global_packet_response_in
 *        in the process
 *
 * @param Takes an endpoint number (0 - 15) to handle the in packet for
 *
 * @note global_packet_response_in is modified to reflect the outcome of the function,
 *       no value is returned
 *
 * @warning This function is intended to be used within an ISR - only use it for this
 *          purpose
 */
void rusb_transfer_handler_in(uint8_t ep_num)
{
    // validate parameter
    assert(ep_num >= 0 && ep_num <= 15);

}

/**
 * @brief Handles OUT packets for a specific endpoint, setting global_packet_response_out
 *        in the process
 *
 * @param Takes an endpoint number (0 - 15) to handle the OUT packet for
 *
 * @note global_packet_response_out is modified to reflect the outcome of the function,
 *       no value is returned
 *
 * @warning This function is intended to be used within an ISR - only use it for this
 *          purpose
 */
void rusb_transfer_handler_out(uint8_t ep_num)
{
    // validate parameter
    assert(ep_num >= 0 && ep_num <= 15);

    // error checks
    if (RUSB_SIE_STATUS & (RUSB_SIE_STATUS_DATA_SEQ_ERROR |
                           RUSB_SIE_STATUS_NAK_REC |
                           RUSB_SIE_STATUS_RX_TIMEOUT |
                           RUSB_SIE_STATUS_RX_OVERFLOW |
                           RUSB_SIE_STATUS_BIT_STUFF_ERROR |
                           RUSB_SIE_STATUS_CRC_ERROR))
    {
        if (RUSB_SIE_STATUS & RUSB_SIE_STATUS_DATA_SEQ_ERROR)
        {
            global_packet_response_out = Data_seq_error;
        }
        else
        {
            global_packet_response_out = Error;
        }

        RUSB_SIE_STATUS &= (~RUSB_SIE_STATUS_DATA_SEQ_ERROR &
                           ~RUSB_SIE_STATUS_NAK_REC &
                           ~RUSB_SIE_STATUS_RX_TIMEOUT &
                           ~RUSB_SIE_STATUS_RX_OVERFLOW &
                           ~RUSB_SIE_STATUS_BIT_STUFF_ERROR &
                           ~RUSB_SIE_STATUS_CRC_ERROR);

        RUSB_BUFF_STATUS &= ~RUSB_BUFF_STATUS_EP_OUT(ep_num);

        return;
    }

    // send stall check
    if (RUSB_DPSRAM_EP_OUT_BUFF_CTRL(ep_num) & RUSB_EP_BUFF_CTRL_BUFF0_SEND_STALL)
    {
        printf("Endpoint %d sent stall (stall bit set).\n", ep_num);
        global_packet_response_out = Stall_sent;
        return;
    }

    // wait for buffer to be available and not full
    while ((RUSB_DPSRAM_EP_OUT_BUFF_CTRL(ep_num) & RUSB_EP_BUFF_CTRL_BUFF0_FULL) ||
            !(RUSB_DPSRAM_EP_OUT_BUFF_CTRL(ep_num) & RUSB_EP_BUFF_CTRL_BUFF0_AVAILABLE))
        ;

    // last buffer check
    if (RUSB_DPSRAM_OUT_BUFF_CTRL(ep_num) & RUSB_EP_BUFF_CTRL_BUFF0_LAST)
    {
        RUSB_DPSRAM_OUT_BUFF_CTRL(ep_num) &= ~RUSB_EP_BUFF_CTRL_BUFF0_LAST;
        RUSB_SIE_STATUS |= RUSB_SIE_STATUS_TRANS_COMPLETE;
        global_packet_response_out = Trans_complete;
        printf("Transfer completed on endpoint %d.\n", ep_num);
    }
    // transaction successful, but not complete
    else
    {
        printf("Transfer completed on endpoint %d.\n", ep_num);
        global_packet_response_out = Trans_done;
    }

    // set buffer bit
    RUSB_BUFF_STATUS |= RUSB_BUFF_STATUS_EP_OUT(ep_num);

    return;
}

