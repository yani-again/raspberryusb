#include <stdint.h>
#include "raspberryusb_drivers.h"
#include "raspberryusb_globals.h"


void raspberryusb_isr(void)
{
    if (RUSB_INTS &= RUSB_INTS_BUS_RESET)
    {
        RUSB_INTS & ~RUSB_INTS_BUS_RESET;
        RUSB_ADDR_ENDP &= 0xFF80;
        global_USB_state = Default;
    }

    // TODO: finish when able to send data
    // if (RUSB_INTS & RUSB_INTS_SETUP_REQ)
}

void raspberryusb_set_defaults(void)
{
    USB_MAIN_CTRL |= 1;
    USB_SIE_CTRL |= (1 << 29) |
                    (1 << 25);
}

