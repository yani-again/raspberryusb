#ifndef RASPBERRYUSB_GLOBALS_H
#define RASPBERRYUSB_GLOBALS_H


typedef enum {
    None, Default, Addressed, Configured, Suspended
} USB_state;


extern USB_state global_USB_state;


#endif
