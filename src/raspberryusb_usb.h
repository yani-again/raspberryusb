#ifndef RASPBERRYUSB_USB_H
#define RASPBERRYUSB_USB_H


#include <stdint.h>


// USB-specification-specific
#define GET_STATUS                   0
#define CLEAR_FEATURE                1
#define SET_FEATURE                  3
#define SET_ADDRESS                  5
#define GET_DESCRIPTOR               6
#define SET_DESCRIPTOR               7
#define GET_CONFIGURATION            8
#define SET_CONFIGURATION            9
#define GET_INTERFACE                10
#define SET_INTERFACE                11
#define SYNCH_FRAME                  12
#define TYPE_DEVICE_DESCRIPTOR              1
#define TYPE_CONFIGURATION_DESCRIPTOR       2
#define TYPE_STRING_DESCRIPTOR              3
#define TYPE_INTERFACE_DESCRIPTOR           4
#define TYPE_ENDPOINT_DESCRIPTOR            5
#define TYPE_DEVICE_QUALIFIER_DESCRIPTOR    6
#define TYPE_OTHER_SPEED_CONFIGURATION      7

// USB ctrl
#define RUSB_USBCTRL_BASE            0x50100000
#define RUSB_USBCTRL_DPSRAM_BASE     0x50100000
#define RUSB_USBCTRL_REGS_BASE       0x50110000
#define RUSB_USBCTRL_DATA_BUFFERS    (uint32_t) (RUSB_CTRL_REGS_BASE + 0x180)

// DPSRAM layout
#define RUSB_DPSRAM_SETUP_PACKET \
            ((volatile uint8_t *) (RUSB_USBCTRL_DPSRAM_BASE + 0x00))
#define RUSB_DPSRAM_EP_IN_CTRL(ep_num)      (*(volatile uint32_t *) \
                                              (RUSB_USBCTRL_REGS_BASE + (ep_num * 8)))
#define RUSB_DPSRAM_EP_OUT_CTRL(ep_num)     (*(volatile uint32_t *) \
                                              (RUSB_USBCTRL_REGS_BASE + (ep_num * 8) + 4))
#define RUSB_DPSRAM_EP_IN_BUFF_CTRL(ep_num) \
            (*(volatile uint32_t *) (RUSB_USBCTRL_REGS_BASE + 0x80 + (ep_num * 8)))
#define RUSB_DPSRAM_EP_OUT_BUFF_CTRL(ep_num) \
            (*(volatile uint32_t *) (RUSB_USBCTRL_REGS_BASE + 0x80 + (ep_num * 8) + 4))
#define RUSB_DPSRAM_EP_IN_OFFSET(ep_num)    (uint32_t) (ep_num * 8)
#define RUSB_DPSRAM_EP_OUT_OFFSET(ep_num)   (uint32_t) (ep_num * 8 + 4)
#define RUSB_DPSRAM_EP_IN_BUFF_OFFSET(ep_num)    (uint32_t) (0x80 + ep_num * 8)
#define RUSB_DPSRAM_EP_OUT_BUFF_OFFSET(ep_num)   (uint32_t) (0x80 + ep_num * 8 + 4)

// endpoint data buffers
#define RUSB_IN_EP0_BUFFER0 \
            ((volatile uint8_t *) (RUSB_USBCTRL_REGS_BASE + 0x100))
/* #define RUSB_IN_EP0_BUFFER1 \
 *             ((volatile uint8_t *) (RUSB_USBCTRL_REGS_BASE + 0x140))
 */
#define RUSB_EP_IN_DATA_BUFFER(ep_num) \
            ((volatile uint8_t *) (RUSB_USBCTRL_DATA_BUFFERS + ep_num * 0x40))
#define RUSB_EP_OUT_DATA_BUFFER(ep_num) \
            ((volatile uint8_t *) (RUSB_USBCTRL_DATA_BUFFERS + ep_num * 0x40 + 0x40))

// endpoint control register
#define RUSB_EP_CTRL_ENABLE          (uint32_t) (1 << 31)
#define RUSB_EP_CTRL_DOUBLE_BUFFERED (uint32_t) (1 << 30)
#define RUSB_EP_CTRL_INT_TRANS       (uint32_t) (1 << 29)
#define RUSB_EP_CTRL_INT_TRANS_DBL   (uint32_t) (1 << 28)
#define RUSB_EP_CTRL_TYPE_CONTROL    (uint32_t) ((0 << 27) | (0 << 26))
#define RUSB_EP_CTRL_TYPE_ISO        (uint32_t) ((0 << 27) | (1 << 26))
#define RUSB_EP_CTRL_TYPE_BULK       (uint32_t) ((1 << 27) | (0 << 26))
#define RUSB_EP_CTRL_TYPE_INTERRUPT  (uint32_t) ((1 << 27) | (1 << 26))
#define RUSB_EP_CTRL_INT_STALL       (uint32_t) (1 << 17)
#define RUSB_EP_CTRL_INT_NAK         (uint32_t) (1 << 16)
#define RUSB_EP_CTRL_BUFF_OFFSET     (uint32_t) 0x0000FFC0

// buffer control register
//#define RUSB_EP_BUFF_CTRL_BUFF1_FULL              (uint32_t) (1 << 31)
//#define RUSB_EP_BUFF_CTRL_BUFF1_LAST              (uint32_t) (1 << 30)
//#define RUSB_EP_BUFF_CTRL_BUFF1_PID               (uint32_t) (1 << 29)
//#define RUSB_EP_BUFF_CTRL_BUFF1_AVAILABLE         (uint32_t) (1 << 26)
#define RUSB_EP_BUFF_CTRL_BUFF0_FULL              (uint32_t) (1 << 15)
#define RUSB_EP_BUFF_CTRL_BUFF0_LAST              (uint32_t) (1 << 14)
#define RUSB_EP_BUFF_CTRL_BUFF0_PID               (uint32_t) (1 << 13)
#define RUSB_EP_BUFF_CTRL_BUFF0_RESET_SELECT      (uint32_t) (1 << 12)
#define RUSB_EP_BUFF_CTRL_BUFF0_SEND_STALL        (uint32_t) (1 << 11)
#define RUSB_EP_BUFF_CTRL_BUFF0_AVAILABLE         (uint32_t) (1 << 10)


// transfer handlers
void rusb_transfer_handler_in(uint8_t ep_num);
void rusb_transfer_handler_out(uint8_t ep_num);

// endpoint data buffers
void rusb_ep_in_buffer(uint8_t ep_num);
void rusb_ep_out_buffer(uint8_t ep_num);


#endif
