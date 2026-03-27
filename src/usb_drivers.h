#ifndef USB_DRIVERS_H
#define USB_DRIVERS_H


#include <stdint.h>


// USB registers
#define RUSB_BASE                   0x50110000
#define RUSB_ADDR_ENDP              ( *(volatile uint32_t *) (USB_BASE + 0x00))
#define RUSB_MAIN_CTRL              ( *(volatile uint32_t *) (USB_BASE + 0x40))
#define RUSB_SIE_CTRL               ( *(volatile uint32_t *) (USB_BASE + 0x4C))
#define RUSB_SIE_STATUS             ( *(volatile uint32_t *) (USB_BASE + 0x50))
#define RUSB_BUFF_STATUS            ( *(volatile uint32_t *) (USB_BASE + 0x58))
#define RUSB_INTE                   ( *(volatile uint32_t *) (USB_BASE + 0x90))
#define RUSB_INTS                   ( *(volatile uint32_t *) (USB_BASE + 0x98))

// register values
#define RUSB_MAIN_CTRL_SIM_TIMING       (uint32_t) (1 << 31)
#define RUSB_MAIN_CTRL_CONTROLLER_EN    (uint32_t) (1 << 0)

#define RUSB_SIE_CTRL_EP0_INT_STALL     (uint32_t) (1 << 31)
#define RUSB_SIE_CTRL_EP0_DOUBLE_BUFF   (uint32_t) (1 << 30)
#define RUSB_SIE_CTRL_EP0_INT1_BUFF     (uint32_t) (1 << 29)
#define RUSB_SIE_CTRL_EP0_INT2_BUFF     (uint32_t) (1 << 28)
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

// TODO: figure out the string concatenation stuff
// #define RUSB_BUFF_STATUS_EP ## ep_num ## _IN    (uint32_t)


typedef enum {
    None, Default, Addressed, Configured, Suspended
} USB_state;


// isr
void raspberryusb_isr(void);

// housekeeping functions
void raspberryusb_reset(void);
void raspberryusb_set_defaults(void);


#endif
