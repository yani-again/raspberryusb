#include <stdint.h>
#include "raspberryusb_descriptors.h"


void rusb_generate_all_descriptors()
{
    rusb_generate_device_descriptor(&device_descriptor);
    rusb_generate_configuration_descriptor(&configuration_descriptor);
    rusb_generate_interface_descriptor(&interface_descriptor);
    rusb_generate_endpoint_descriptor(&endpoint_descriptor_1_in);
    rusb_generate_endpoint_descriptor(&endpoint_descriptor_1_out);
    rusb_generate_hid_descriptor(&hid_descriptor);
}

// generation functions
/**
 * @brief Initialises the USB device descriptor with some default values.
 *
 * This function takes a pointer to `raspberryusb_device_descriptor` struct and sets
 * all 14 fields to pre-determined values. These values are NOT set in stone and can
 * later be changed, this function is simply to set default values, as most of them will
 * not need to be changed.
 *
 * @param A pointer to `raspberryusb_device_descriptor` that will be initialised with
 *        default values.
 *
 * @note All fields are modified. For a full list of their initial values, see
 *       the documentation.
 *
 * @warning Ensure the pointer parameter is valid prior to the function call and is
 *          not NULL.
 */
void rusb_generate_device_descriptor(rusb_device_descriptor* descriptor)
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
    descriptor->iManufacturer = 0x01;
    descriptor->iProduct = 0x02;
    descriptor->iSerialNumber = 0x03;
    descriptor->bNumConfigurations = 0x01;
}

/**
 * @brief Initialises the USB configuration descriptor with some default values.
 *
 * Params, notes, and warnings are identical to `generate_device_descriptor()`, reference
 * that function for further details.
 */
void rusb_generate_configuration_descriptor(rusb_configuration_descriptor* descriptor)
{
    descriptor->bLength = 0x09;
    descriptor->bDescriptorType = 0x02;
    descriptor->wTotalLength = 0x0000;
    descriptor->bNumInterfaces = 0x01;
    descriptor->bConfigurationValue = 0x01;
    descriptor->iConfiguration = 0x00;
    descriptor->bmAttributes = 0x00;
    descriptor->MaxPower = 0x00;
}

/**
 * @brief Initialises the USB interface descriptor with some default values.
 *
 * Params, notes, and warnings are identical to `generate_device_descriptor()`, reference
 * that function for further details.
 */
void rusb_generate_interface_descriptor(rusb_interface_descriptor* descriptor)
{
    descriptor->bLength = 0x09;
    descriptor->bDescriptorType = 0x04;
    descriptor->bInterfaceNumber = 0x00;
    descriptor->bAlternateSetting = 0x00;
    descriptor->bNumEndpoints = 0x00;
    descriptor->bInterfaceClass = 0x03;
    descriptor->bInterfaceSubClass = 0x00;
    descriptor->bInterfaceProtocol = 0x00;
    descriptor->iInterface = 0x00;
}

/**
 * @brief Initialises the USB endpoint descriptor with some default values.
 *
 * Params, notes, and warnings are identical to `generate_device_descriptor()`, reference
 * that function for further details.
 */
void rusb_generate_endpoint_descriptor(rusb_endpoint_descriptor* descriptor)
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
void rusb_generate_hid_descriptor(rusb_hid_descriptor* descriptor)
{
    descriptor->bLength = 0x09;
    descriptor->bDescriptorType = 0x21;
    descriptor->bcdHID = 0x1101;
    descriptor->bCountryCode = 0x00;
    descriptor->bNumDescriptors = 0x01;
    descriptor->bDescriptorType = 0x22;
    descriptor->wDescriptorLength = 0x0000;
}


// value setter functions
/**
 * @brief Modifies a specific field within a device descriptor using a provided value.
 *
 * @param `field` specifies which field to modify (see all available options in the
 *        specification), `descriptor` is a pointer to a device descriptor struct, and
 *        `value` is the value to set within the specified field.
 *
 * @note 16-bit fields must be provided little-endian (as per the USB specification), as
 *       RaspberryUSB does not change the endianness automatically.
 */
void rusb_device_descriptor_set(uint8_t field, rusb_device_descriptor* descriptor, uint16_t value)
{
    switch (field)
    {
        case RUSB_DEVICE_DESCRIPTOR_BDEVICECLASS:
            descriptor->bDeviceClass = value;
            break;
        case RUSB_DEVICE_DESCRIPTOR_BDEVICESUBCLASS:
            descriptor->bDeviceSubClass = value;
            break;
        case RUSB_DEVICE_DESCRIPTOR_BDEVICEPROTOCOL:
            descriptor->bDeviceProtocol = value;
            break;
        case RUSB_DEVICE_DESCRIPTOR_IDVENDOR:
            descriptor->idVendor = (uint8_t) value;
            break;
        case RUSB_DEVICE_DESCRIPTOR_IDPRODUCT:
            descriptor->idProduct = (uint8_t) value;
            break;
        case RUSB_DEVICE_DESCRIPTOR_BCDDEVICE:
            descriptor->bcdDevice = (uint8_t) value;
            break;
        case RUSB_DEVICE_DESCRIPTOR_IMANUFACTURER:
            descriptor->Imanufacturer = value;
            break;
        case RUSB_DEVICE_DESCRIPTOR_IPRODUCT:
            descriptor->iProduct = value;
            break;
        case RUSB_DEVICE_DESCRIPTOR_ISERIALNUMBER:
            descriptor->iSerialNumber = value;
            break;
    }
}

/**
 * @brief Same functionality as `rusb_device_descriptor`, see the notes for that.
 */
void rusb_configuration_descriptor(uint8_t field, rusb_configuration_descriptor* descriptor, uint16_t value)
{
    switch (field)
    {
        case RUSB_CONFIGURATION_DESCRIPTOR_WTOTALLENGTH:
            descriptor->wTotalLength = value;
            break;
        case RUSB_CONFIGURATION_DESCRIPTOR_BNUMINTERFACES:
            descriptor->bNumInterfaces = (uint8_t) value;
            break;
        case RUSB_CONFIGURATION_DESCRIPTOR_BMATTRIBUTES:
            descriptor->bmAttributes = (uint8_t) value;
            break;
        case RUSB_CONFIGURATION_DESCRIPTOR_MAXPOWER:
            descriptor->MaxPower = (uint8_t) value;
            break;
    }
}

/**
 * @brief Same functionality as `rusb_device_descriptor`, see the notes for that.
 */
void rusb_interface_descriptor(uint8_t field, rusb_interface_descriptor* descriptor, uint16_t value)
{
    switch (field)
    {
        case RUSB_INTERFACE_DESCRIPTOR_BINTERFACENUMBER:
            descriptor->bInterfaceNumber = (uint8_t) value;
            break;
        case RUSB_INTERFACE_DESCRIPTOR_BALTERNATESETTING:
            descriptor->bAlternateSetting = (uint8_t) value;
            break;
        case RUSB_INTERFACE_DESCRIPTOR_BNUMENDPOINTS:
            descriptor->bNumEndpoints = (uint8_t) value;
            break;
        case RUSB_INTERFACE_DESCRIPTOR_BINTERFACECLASS:
            descriptor->bInterfaceClass = (uint8_t) value;
            break;
        case RUSB_INTERFACE_DESCRIPTOR_BINTERFACESUBCLASS:
            descriptor->bInterfaceSubClass = (uint8_t) value;
            break;
        case RUSB_INTERFACE_DESCRIPTOR_BINTERFACEPROTOCOL:
            descriptor->bInterfaceProtocol = (uint8_t) value;
            break;
        case RUSB_INTERFACE_DESCRIPTOR_IINTERFACE:
            descriptor->iInterface = (uint8_t) value;
            break;
    }
}

/**
 * @brief Same functionality as `rusb_device_descriptor`, see the notes for that.
 */
void rusb_endpoint_descriptor(uint8_t field, rusb_endpoint_descriptor* descriptor, uint16_t value)
{
    switch (field)
    {
        case RUSB_ENDPOINT_DESCRIPTOR_BENDPOINTADDRESS:
            descriptor->bEndpointAddress = (uint8_t) value;
            break;
        case RUSB_ENDPOINT_DESCRIPTOR_BMATTRIBUTES:
            descriptor->bmAttributes = (uint8_t) value;
            break;
        case RUSB_ENDPOINT_DESCRIPTOR_WMAXPACKETSIZE:
            descriptor->wMaxPacketSize = value;
            break;
        case RUSB_ENDPOINT_DESCRIPTOR_BINTERVAL:
            descriptor->bInterval = (uint8_t) value;
            break;
    }
}

/**
 * @brief Same functionality as `rusb_device_descriptor`, see the notes for that.
 */
void rusb_hid_descriptor(uint8_t field, rusb_hid_descriptor* descriptor, uint16_t value)
{
    switch (field)
    {
        case RUSB_HID_DESCRIPTOR_BCOUNTRYCODE:
            descriptor->bCountryCode = (uint8_t) value;
            break;
        case RUSB_HID_DESCRIPTOR_BNUMDESCRIPTORS:
            descriptor->bNumDescriptors = (uint8_t) value;
            break;
        case RUSB_HID_DESCRIPTOR_BDESCRIPTORTYPE:
            descriptor->bDescriptorType = (uint8_t) value;
            break;
        case RUSB_HID_DESCRIPTOR_WDESCRIPTORLENGTH:
            descriptor->wDescriptorLength = value;
            break;
    }
}


void rusb_set_report_descriptor(const uint8_t *extern_descriptor)
{
    rusb_report_descriptor = extern_descriptor;
}

void rusb_set_string_descriptor_manufacturer(const uint8_t *extern_descriptor)
{
    rusb_string_descriptor_manufacturer = extern_descriptor;
}

void rusb_set_string_descriptor_product(const uint8_t *extern_descriptor)
{
    rusb_string_descriptor_product = extern_descriptor;
}

void rusb_set_string_descriptor_serial_number(const uint8_t *extern_descriptor)
{
    rusb_string_descriptor_serial_number = extern_descriptor;
}

