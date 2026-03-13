#ifndef USB_DRIVERS_H
#define USB_DRIVERS_H


#include <stdint.h>


// USB registers
#define USB_BASE            0x50110000
#define USB_ADDR_ENDP       ( *(volatile uint32_t *) (USB_BASE + 0x00))
#define USB_MAIN_CTRL       ( *(volatile uint32_t *) (USB_BASE + 0x40))
#define USB_SIE_CTRL        ( *(volatile uint32_t *) (USB_BASE + 0x4C))
#define USB_SIE_STATUS      ( *(volatile uint32_t *) (USB_BASE + 0x50))
#define USB_BUFF_STATUS     ( *(volatile uint32_t *) (USB_BASE + 0x58))
#define USB_INTE            ( *(volatile uint32_t *) (USB_BASE + 0x90))


typedef enum {
    Default, Addressed, Configured, Suspended
} USB_state;

typedef struct {
    uint8_t 
}


#endif
