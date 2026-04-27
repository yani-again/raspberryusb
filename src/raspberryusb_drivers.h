#ifndef RASPBERRYUSB_DRIVERS_H
#define RASPBERRYUSB_DRIVERS_H


#include <stdint.h>
#include "raspberryusb_globals.h"


// USB registers
#define RUSB_BASE                   0x50110000
#define RUSB_ADDR_ENDP              ( *(volatile uint32_t *) (RUSB_BASE + 0x00))
#define RUSB_MAIN_CTRL              ( *(volatile uint32_t *) (RUSB_BASE + 0x40))
#define RUSB_SIE_CTRL               ( *(volatile uint32_t *) (RUSB_BASE + 0x4C))
#define RUSB_SIE_STATUS             ( *(volatile uint32_t *) (RUSB_BASE + 0x50))
#define RUSB_BUFF_STATUS            ( *(volatile uint32_t *) (RUSB_BASE + 0x58))
#define RUSB_EP_STALL_ARM           ( *(volatile uint32_t *) (RUSB_BASE + 0x68))
#define RUSB_INTE                   ( *(volatile uint32_t *) (RUSB_BASE + 0x90))
#define RUSB_INTS                   ( *(volatile uint32_t *) (RUSB_BASE + 0x98))

// register values
#define RUSB_MAIN_CTRL_SIM_TIMING       (uint32_t) (1 << 31)
#define RUSB_MAIN_CTRL_CONTROLLER_EN    (uint32_t) (1 << 0)
#define RUSB_MAIN_CTRL_HOST_NDEVICE     (uint32_t) (1 << 1)

#define RUSB_SIE_CTRL_EP0_INT_STALL     (uint32_t) (1 << 31)
#define RUSB_SIE_CTRL_EP0_DOUBLE_BUFF   (uint32_t) (1 << 30)
#define RUSB_SIE_CTRL_EP0_INT_1BUFF     (uint32_t) (1 << 29)
#define RUSB_SIE_CTRL_EP0_INT_2BUFF     (uint32_t) (1 << 28)
#define RUSB_SIE_CTRL_EP0_INT_NAK       (uint32_t) (1 << 27)
#define RUSB_SIE_CTRL_DIRECT_EN         (uint32_t) (1 << 26)
#define RUSB_SIE_CTRL_DIRECT_DP         (uint32_t) (1 << 25)
#define RUSB_SIE_CTRL_DIRECT_DM         (uint32_t) (1 << 24)
#define RUSB_SIE_CTRL_TRANSCEIVER_PD    (uint32_t) (1 << 18)
#define RUSB_SIE_CTRL_RPU_OPT           (uint32_t) (1 << 17)
#define RUSB_SIE_CTRL_PULLUP_EN         (uint32_t) (1 << 16)
#define RUSB_SIE_CTRL_PULLDOWN_EN       (uint32_t) (1 << 15)
#define RUSB_SIE_CTRL_RESUME            (uint32_t) (1 << 12)

#define RUSB_SIE_STATUS_DATA_SEQ_ERROR  (uint32_t) (1 << 31)
#define RUSB_SIE_STATUS_ACK_REC         (uint32_t) (1 << 30)
#define RUSB_SIE_STATUS_STALL_REC       (uint32_t) (1 << 29)
#define RUSB_SIE_STATUS_NAK_REC         (uint32_t) (1 << 28)
#define RUSB_SIE_STATUS_RX_TIMEOUT      (uint32_t) (1 << 27)
#define RUSB_SIE_STATUS_RX_OVERFLOW     (uint32_t) (1 << 26)
#define RUSB_SIE_STATUS_BIT_STUFF_ERROR (uint32_t) (1 << 25)
#define RUSB_SIE_STATUS_CRC_ERROR       (uint32_t) (1 << 24)
#define RUSB_SIE_STATUS_BUS_RESET       (uint32_t) (1 << 19)
#define RUSB_SIE_STATUS_TRANS_COMPLETE  (uint32_t) (1 << 18)
#define RUSB_SIE_STATUS_SETUP_REC       (uint32_t) (1 << 17)
#define RUSB_SIE_STATUS_CONNECTED       (uint32_t) (1 << 16)
#define RUSB_SIE_STATUS_RESUME          (uint32_t) (1 << 11)
#define RUSB_SIE_STATUS_VBUS_OVER_CURR  (uint32_t) (1 << 10)
#define RUSB_SIE_STATUS_SUSPENDED       (uint32_t) (1 << 4)
#define RUSB_SIE_STATUS_LINE_STATE      (uint32_t) ((1 << 3) | (1 << 2))
#define RUSB_SIE_STATUS_VBUS_DETECTED   (uint32_t) (1 << 0)

#define RUSB_BUFF_STATUS_EP_IN(ep_num)  (uint32_t) (1 << (2 * ep_num))
#define RUSB_BUFF_STATUS_EP_OUT(ep_num) (uint32_t) (1 << (2 * ep_num + 1))

#define RUSB_EP_STALL_ARM_EP0_OUT       (uint32_t) (1 << 1)
#define RUSB_EP_STALL_ARM_EP0_IN        (uint32_t) (1 << 0)

#define RUSB_INTE_EP_STALL_NAK          (uint32_t) (1 << 19)
#define RUSB_INTE_ABORT_DONE            (uint32_t) (1 << 18)
#define RUSB_INTE_DEV_SOF               (uint32_t) (1 << 17)
#define RUSB_INTE_SETUP_REQ             (uint32_t) (1 << 16)
#define RUSB_INTE_DEV_RESUME_FROM_HOST  (uint32_t) (1 << 15)
#define RUSB_INTE_DEV_SUSPEND           (uint32_t) (1 << 14)
#define RUSB_INTE_DEV_CONN_DIS          (uint32_t) (1 << 13)
#define RUSB_INTE_BUS_RESET             (uint32_t) (1 << 12)
#define RUSB_INTE_VBUS_DETECT           (uint32_t) (1 << 11)
#define RUSB_INTE_STALL                 (uint32_t) (1 << 10)
#define RUSB_INTE_ERROR_CRC             (uint32_t) (1 << 9)
#define RUSB_INTE_ERROR_BIT_STUFF       (uint32_t) (1 << 8)
#define RUSB_INTE_ERROR_RX_OVERFLOW     (uint32_t) (1 << 7)
#define RUSB_INTE_ERROR_RX_TIMEOUT      (uint32_t) (1 << 6)
#define RUSB_INTE_ERROR_DATA_SEQ        (uint32_t) (1 << 5)
#define RUSB_INTE_BUFF_STATUS           (uint32_t) (1 << 4)
#define RUSB_INTE_TRANS_COMPLETE        (uint32_t) (1 << 3)

#define RUSB_INTS_EP_STALL_NAK          (uint32_t) (1 << 19)
#define RUSB_INTS_ABORT_DONE            (uint32_t) (1 << 18)
#define RUSB_INTS_DEV_SOF               (uint32_t) (1 << 17)
#define RUSB_INTS_SETUP_REQ             (uint32_t) (1 << 16)
#define RUSB_INTS_DEV_RESUME_FROM_HOST  (uint32_t) (1 << 15)
#define RUSB_INTS_DEV_SUSPEND           (uint32_t) (1 << 14)
#define RUSB_INTS_DEV_CONN_DIS          (uint32_t) (1 << 13)
#define RUSB_INTS_BUS_RESET             (uint32_t) (1 << 12)
#define RUSB_INTS_VBUS_DETECT           (uint32_t) (1 << 11)
#define RUSB_INTS_STALL                 (uint32_t) (1 << 10)
#define RUSB_INTS_ERROR_CRC             (uint32_t) (1 << 9)
#define RUSB_INTS_ERROR_BIT_STUFF       (uint32_t) (1 << 8)
#define RUSB_INTS_ERROR_RX_OVERFLOW     (uint32_t) (1 << 7)
#define RUSB_INTS_ERROR_RX_TIMEOUT      (uint32_t) (1 << 6)
#define RUSB_INTS_ERROR_DATA_SEQ        (uint32_t) (1 << 5)
#define RUSB_INTS_BUFF_STATUS           (uint32_t) (1 << 4)
#define RUSB_INTS_TRANS_COMPLETE        (uint32_t) (1 << 3)


// isr
void rusb_isr(void);

// housekeeping
void rusb_reset(void);
void rusb_enable_usb(void);

// packet handling
void rusb_load_descriptor(uint8_t wDescriptorType, uint8_t wDescriptorIndex, uint16_t wLength);
volatile uint8_t* rusb_handle_out_packet(void);
void rusb_handle_in_packet(uint8_t ep_num, rusb_packet_response_in to_send);

// endpoint functions
void rusb_setup_out_endpoint(uint8_t ep_num, uint32_t ep_type);
void rusb_setup_in_endpoint(uint8_t ep_num, uint32_t ep_type);


#endif
