#ifndef USB_DESCRIPTORS_H
#define USB_DESCRIPTORS_H


#include <stdint.h>


typedef struct {
    uint8_t  bLength,
    uint8_t  bDescriptorType,
    uint16_t bcdUSB,
    uint8_t  bDeviceClass,
    uint8_t  bDeviceSubclass,
    uint8_t  bDeviceProtocol,
    uint8_t  bMaxPacketSize0,
    uint16_t idVendor,
    uint16_t idProduct,
    uint16_t bcdDevice,
    uint8_t  iManufacturer,
    uint8_t  iProduct,
    uint8_t  iSerialNumber,
    uint8_t  bNumConfigurations
} raspberryusb_device_descriptor;

typedef struct {
    uint8_t  bLength,
    uint8_t  bDescriptorType,
    uint16_t wTotalLength,
    uint8_t  bNumInterfaces,
    uint8_t  bConfigurationValue,
    uint8_t  iConfiguration,
    uint8_t  bmAttributes,
    uint8_t  MaxPower
} raspberryusb_configuration_descriptor;

typedef struct {
    uint8_t bLength,
    uint8_t bDescriptorType,
    uint8_t bInterfaceNumber,
    uint8_t bAlternateSetting,
    uint8_t bNumEndpoints,
    uint8_t bInterfaceClass,
    uint8_t bInterfaceSubClass,
    uint8_t bInterfaceProtocol,
    uint8_t iInterface
} raspberryusb_interface_descriptor;

typedef struct {
    uint8_t  bLength,
    uint8_t  bDescriptorType,
    uint8_t  bEndpointAddress,
    uint8_t  bmAttributes,
    uint16_t wMaxPacketSize,
    uint8_t  bInterval
} raspberryusb_endpoint_descriptor;

typedef struct {
    uint8_t  bLength,
    uint8_t  bDescriptorType,
    uint16_t bcdHID,
    uint8_t  bCountryCode,
    uint8_t  bNumDescriptors,
    uint8_t  bDescriptorType,
    uint16_t wDescriptorLength
} raspberryusb_hid_descriptor;


#endif
