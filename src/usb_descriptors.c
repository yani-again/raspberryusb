#include <stdint.h>
#include "usb_descriptors.h"


/**
 * @brief Initialises the USB device descriptor with some default values.
 *
 * This function takes a pointer to `raspberryusb_device_descriptor` struct and sets
 * all 14 fields to pre-determined values. These values are NOT set in stone and can
 * later be changed, this function is simply to set default values, as most of them will
 * not need to be changed.
 *
 * @param A pointer to `raspberryusb_device_descriptor` that will be initialised with
 *        default values
 *
 * @note All fields are modified. For a full list of their initial values, see
 *       the documentation.
 *
 * @warning Ensure the pointer parameter is valid prior to the function call and is
 *          not NULL.
 */
void generate_device_descriptor(raspberryusb_device_descriptor* descriptor)
{
    descriptor->bLength = 0x12;
    descriptor->bDescriptorType = 0x01;
    descriptor->bcdUSB = 0x0002;
    descriptor->bDeviceClass = 0x00;
    descriptor->bDeviceSubClass = 0x00;
    descriptor->bDeviceprotocol = 0x00;
    descriptor->bMaxPacketSize0 = 0x40;
    descriptor->idVendor = 0x0000;
    descriptor->idProduct = 0x0000;
    descriptor->bcdDevice = 0x0100;
    descriptor->iManufacturer = 0x00;
    descriptor->iProduct = 0x01;
    descriptor->iSerialNumber = 0x02;
    descriptor->bNumConfigurations = 0x01;
}

/**
 * @brief Initialises the USB configuration descriptor with some default values.
 *
 * Params, notes, and warnings are identical to `generate_device_descriptor()`, reference
 * that function for further details.
 */
void generate_configuration_descriptor(raspberryusb_configuration_descriptor* descriptor)
{
    descriptor->bLength = 0x09;
    descriptor->bDescriptorType = 0x02;
    descriptor->wTotalLength = 0x0000;
    descriptor->bNumInterfaces = 0x01;
    descriptor->bConfigurationValue = 0x01;
    descriptor->iConfiguration = 0x03;
    descriptor->bmAttributes = 0x00;
    descriptor->MaxPower = 0x00;
}

/**
 * @brief Initialises the USB interface descriptor with some default values.
 *
 * Params, notes, and warnings are identical to `generate_device_descriptor()`, reference
 * that function for further details.
 */
void generate_interface_descriptor(raspberryusb_interface_descriptor* descriptor)
{
    descriptor->bLength = 0x09;
    descriptor->bDescriptorType = 0x04;
    descriptor->bInterfaceNumber = 0x00;
    descriptor->bAlternateSetting = 0x00;
    descriptor->bNumEndpoints = 0x00;
    descriptor->bInterfaceClass = 0x03;
    descriptor->bInterfaceSubClass = 0x00;
    descriptor->bInterfaceProtocol = 0x00;
    descriptor->iInterface = 0x04;
}

/**
 * @brief Initialises the USB endpoint descriptor with some default values.
 *
 * Params, notes, and warnings are identical to `generate_device_descriptor()`, reference
 * that function for further details.
 */
void generate_endpoint_descriptor(raspberryusb_endpoint_descriptor* descriptor)
{
    descriptor->bLength = 0x07;
    descriptor->bDescriptorType = 0x05;
    descriptor->bEndpointAddress = 0x00;
    descriptor->bmAttributes = 0x00;
    descriptor->wMaxPacketSize = 0x0000;
    descriptor->bInterval = 0x00;
}

/**
 * @brief Initialises the USB HID descriptor with some default values.
 *
 * Params, notes, and warnings are identical to `generate_device_descriptor()`, reference
 * that function for further details.
 */
void generate_hid_descriptor(raspberryusb_hid_descriptor* descriptor)
{
    descriptor-> = 0x09;
    descriptor-> = 0x21;
    descriptor-> = 0x1011;
    descriptor-> = 0x00;
    descriptor-> = 0x01;
    descriptor-> = 0x22;
    descriptor-> = 0x0000;
}

