#ifndef USB_DESCRIPTORS_H
#define USB_DESCRIPTORS_H


#include <stdint.h>


// report descriptor values
// main items
// input
#define M_IN_DATA           (uint8_t) (0 << 0)
#define M_IN_CONSTANT       (uint8_t) (1 << 0)
#define M_IN_ARRAY          (uint8_t) (0 << 1)
#define M_IN_VARIABLE       (uint8_t) (1 << 1)
#define M_IN_ABSOLUTE       (uint8_t) (0 << 2)
#define M_IN_RELATIVE       (uint8_t) (1 << 2)
#define M_IN_NO_WRAP        (uint8_t) (0 << 3)
#define M_IN_WRAP           (uint8_t) (1 << 3)
#define M_IN_LINEAR         (uint8_t) (0 << 4)
#define M_IN_NON_LINEAR     (uint8_t) (1 << 4)
#define M_IN_PREFERRED      (uint8_t) (0 << 5)
#define M_IN_NO_PREFERRED   (uint8_t) (1 << 5)
#define M_IN_NO_NULL_STATE  (uint8_t) (0 << 6)
#define M_IN_NULL_STATE     (uint8_t) (1 << 6)
#define M_IN_BIT_FIELD      (uint8_t) (0 << 8)
#define M_IN_BUFFERED       (uint8_t) (1 << 8)

// output
#define M_OU_DATA           (uint8_t) (0 << 0)
#define M_OU_CONSTANT       (uint8_t) (1 << 0)
#define M_OU_ARRAY          (uint8_t) (0 << 1)
#define M_OU_VARIABLE       (uint8_t) (1 << 1)
#define M_OU_ABSOLUTE       (uint8_t) (0 << 2)
#define M_OU_RELATIVE       (uint8_t) (1 << 2)
#define M_OU_NO_WRAP        (uint8_t) (0 << 3)
#define M_OU_WRAP           (uint8_t) (1 << 3)
#define M_OU_LINEAR         (uint8_t) (0 << 4)
#define M_OU_NON_LINEAR     (uint8_t) (1 << 4)
#define M_OU_PREFERRED      (uint8_t) (0 << 5)
#define M_OU_NO_PREFERRED   (uint8_t) (1 << 5)
#define M_OU_NO_NULL_STATE  (uint8_t) (0 << 6)
#define M_OU_NULL_STATE     (uint8_t) (1 << 6)
#define M_OU_NON_VOLATILE   (uint8_t) (0 << 7)
#define M_OU_VOLATILE       (uint8_t) (1 << 7)
#define M_OU_BIT_FIELD      (uint8_t) (0 << 8)
#define M_OU_BUFFERED       (uint8_t) (1 << 8)

// feature
#define M_FE_DATA           (uint8_t) (0 << 0)
#define M_FE_CONSTANT       (uint8_t) (1 << 0)
#define M_FE_ARRAY          (uint8_t) (0 << 1)
#define M_FE_VARIABLE       (uint8_t) (1 << 1)
#define M_FE_ABSOLUTE       (uint8_t) (0 << 2)
#define M_FE_RELATIVE       (uint8_t) (1 << 2)
#define M_FE_NO_WRAP        (uint8_t) (0 << 3)
#define M_FE_WRAP           (uint8_t) (1 << 3)
#define M_FE_LINEAR         (uint8_t) (0 << 4)
#define M_FE_NON_LINEAR     (uint8_t) (1 << 4)
#define M_FE_PREFERRED      (uint8_t) (0 << 5)
#define M_FE_NO_PREFERRED   (uint8_t) (1 << 5)
#define M_FE_NO_NULL_STATE  (uint8_t) (0 << 6)
#define M_FE_NULL_STATE     (uint8_t) (1 << 6)
#define M_FE_NON_VOLATILE   (uint8_t) (0 << 7)
#define M_FE_VOLATILE       (uint8_t) (1 << 7)
#define M_FE_BIT_FIELD      (uint8_t) (0 << 8)
#define M_FE_BUFFERED       (uint8_t) (1 << 8)

// collection
#define M_CO_PHYSICAL       (uint8_t) 0x00
#define M_CO_APPLICATION    (uint8_t) 0x01
#define M_CO_LOGICAL        (uint8_t) 0x02
#define M_CO_REPORT         (uint8_t) 0x03
#define M_CO_NAMED_ARRAY    (uint8_t) 0x04
#define M_CO_USAGE_SWITCH   (uint8_t) 0x05
#define M_CO_USAGE_MODIFIER (uint8_t) 0x06

// end collection
#define M_END_COLLECTION    (uint8_t) ((1 << 7) | (1 << 6))


// global items
#define G_USAGE_PAGE        (uint8_t) (1 << 2)
#define G_LOGICAL_MIN       (uint8_t) ((1 << 4) | (1 << 2))
#define G_LOGICAL_MAX       (uint8_t) ((1 << 5) | (1 << 2))
#define G_PHYSICAL_MIN      (uint8_t) ((1 << 5) | (1 << 4) | (1 << 2))
#define G_PHYSICAL_MAX      (uint8_t) ((1 << 6) | (1 << 2))
#define G_UNIT_EXPONENT     (uint8_t) ((1 << 6) | (1 << 4) | (1 << 2))
#define G_UNIT              (uint8_t) ((1 << 6) | (1 << 5) | (1 << 2))
#define G_REPORT_SIZE       (uint8_t) ((1 << 6) | (1 << 5) | (1 << 4) | (1 << 2))
#define G_REPORT_ID         (uint8_t) ((1 << 7) | (1 << 2))
#define G_REPORT_COUNT      (uint8_t) ((1 << 7) | (1 << 4) | (1 << 2))
#define G_PUSH              (uint8_t) ((1 << 7) | (1 << 5) | (1 << 2))
#define G_POP               (uint8_t) ((1 << 7) | (1 << 5) | (1 << 4) | (1 << 2))


// local items
#define L_USAGE             (uint8_t) ((1 << 3))
#define L_USAGE_MIN         (uint8_t) ((1 << 4) | (1 << 3))
#define L_USAGE_MAX         (uint8_t) ((1 << 5) | (1 << 3))
#define L_DESIG_INDEX       (uint8_t) ((1 << 5) | (1 << 4) | (1 << 3))
#define L_DESIG_MIN         (uint8_t) ((1 << 6) | (1 << 3))
#define L_DESIG_MAX         (uint8_t) ((1 << 6) | (1 << 4) | (1 << 3))
#define L_STR_INDEX         (uint8_t) ((1 << 6) | (1 << 5) | (1 << 4) | (1 << 3))
#define L_STR_MIN           (uint8_t) ((1 << 7) | (1 << 3))
#define L_STR_MAX           (uint8_t) ((1 << 7) | (1 << 4) | (1 << 3))
#define L_DELIMITER         (uint8_t) ((1 << 7) | (1 << 5) | (1 << 3))


// descriptor structs
typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t bcdUSB;
    uint8_t  bDeviceClass;
    uint8_t  bDeviceSubclass;
    uint8_t  bDeviceProtocol;
    uint8_t  bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t  iManufacturer;
    uint8_t  iProduct;
    uint8_t  iSerialNumber;
    uint8_t  bNumConfigurations;
} raspberryusb_device_descriptor;

typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t wTotalLength;
    uint8_t  bNumInterfaces;
    uint8_t  bConfigurationValue;
    uint8_t  iConfiguration;
    uint8_t  bmAttributes;
    uint8_t  MaxPower;
} raspberryusb_configuration_descriptor;

typedef struct {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
} raspberryusb_interface_descriptor;

typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bEndpointAddress;
    uint8_t  bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t  bInterval;
} raspberryusb_endpoint_descriptor;

typedef struct {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t bcdHID;
    uint8_t  bCountryCode;
    uint8_t  bNumDescriptors;
    uint8_t  bDescriptorType;
    uint16_t wDescriptorLength;
} raspberryusb_hid_descriptor;


// descriptor-generation functions
void generate_device_descriptor(raspberryusb_device_descriptor* descriptor);
void generate_configuration_descriptor(raspberryusb_configuration_descriptor* descriptor);
void generate_interface_descriptor(raspberryusb_interface_descriptor* descriptor);
void generate_endpoint_descriptor(raspberryusb_endpoint_descriptor* descriptor);
void generate_hid_descriptor(raspberryusb_hid_descriptor* descriptor);


// descriptor setter functions


#endif
