## Creating Descriptors

### Declaring
Descriptor structs available to use for descriptor declaration:
- `raspberryusb_device_descriptor`
- `raspberryusb_configuration_descriptor`
- `raspberryusb_interface_descriptor`
- `raspberryusb_endpoint_descriptor`
- `raspberryusb_hid_descriptor`

Example declarations:
```c
raspberryusb_device_descriptor device_descriptor;
raspberryusb_configuration_descriptor configuration_descriptor;
```

Descriptor initialisation is **discouraged**, use the functions below instead.

### Descriptor Initialisation
Declared descriptors can be initialised using initialisation functions, which simply set default values:
- `void generate_device_descriptor(raspberryusb_device_descriptor* descriptor)`
- `void generate_configuration_descriptor(raspberryusb_configuration_descriptor* descriptor)`
- `void generate_interface_descriptor(raspberryusb_interface_descriptor* descriptor)`
- `void generate_endpoint_descriptor(raspberryusb_endpoint_descriptor* descriptor)`
- `void generate_hid_descriptor(raspberryusb_hid_descriptor* descriptor)`

#### Default Values
Complete list of what every descriptor type looks after default initialisation, **all are little-endian.**

##### Device Descriptor
```c
uint8_t  bLength            = 0x12
uint8_t  bDescriptorType    = 0x01
uint16_t bcdUSB             = 0x0002
uint8_t  bDeviceClass       = 0x00
uint8_t  bDeviceSubclass    = 0x00
uint8_t  bDeviceProtocol    = 0x00
uint8_t  bMaxPacketSize0    = 0x40
uint16_t idVendor           = 0x0000
uint16_t idProduct          = 0x0000
uint16_t bcdDevice          = 0x0100
uint8_t  iManufacturer      = 0x00
uint8_t  iProduct           = 0x01
uint8_t  iSerialNumber      = 0x02
uint8_t  bNumConfigurations = 0x01
```

##### Configuration Descriptor
```c
uint8_t  bLength                = 0x09;
uint8_t  bDescriptorType        = 0x02;
uint16_t wTotalLength           = 0x0000;
uint8_t  bNumInterfaces         = 0x01;
uint8_t  bConfigurationValue    = 0x01;
uint8_t  iConfiguration         = 0x03;
uint8_t  bmAttributes           = 0x00;
uint8_t  MaxPower               = 0x00;
```

##### Interface Descriptor
```c
uint8_t  bLength            = 0x09;
uint8_t  bDescriptorType    = 0x04;
uint8_t  bInterfaceNumber   = 0x00;
uint8_t  bAlternateSetting  = 0x00;
uint8_t  bNumEndpoints      = 0x00;
uint8_t  bInterfaceClass    = 0x03;
uint8_t  bInterfaceSubClass = 0x00;
uint8_t  bInterfaceProtocol = 0x00;
uint8_t  iInterface         = 0x04;
```

When generating a device descriptor using `generate_device_descriptor()`:
- bDeviceClass, bDeviceSubClass, and bDeviceProtocol are set to `0x00` by default
- bMaxPacketSize0 is set to `0x40`
- iManufacturer, iProduct, and iSerialNumber are `0x00`

**All of the above default values can be changed by their respective setter functions, listed below.**

### Descriptor Setter Functions
