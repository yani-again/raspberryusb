#include <stdint.h>
#include "usb_descriptors.h"


raspberryusb_device_descriptor* generate_device_descriptor(void);
raspberryusb_configuration_descriptor* generate_configuration_descriptor(void);
raspberryusb_interface_descriptor* generate_interface_descriptor(void);
raspberryusb_endpoint_descriptor* generate_endpoint_descriptor(void);
raspberryusb_hid_descriptor* generate_hid_descriptor(void);


