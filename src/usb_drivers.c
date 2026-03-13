#include <stdint.h>
#include "usb_drivers.h"


void isr_usb(void);


int main(void)
{
    USB_state state = Default;

    // USB setup
    

    // USB enable
    USB_MAIN_CTRL |= 1;
    USB_SIE_CTRL |= (1 << 29) |
                    (1 << 25);
}

void isr_usb(void)
{
    if (USB_SIE_STATUS & (1 << 19))
    {
        
    }
}
