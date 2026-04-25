#ifndef RASPBERRYUSB_DESCRIPTORS_H
#define RASPBERRYUSB_DESCRIPTORS_H


#include <stdint.h>
#include "raspberryusb_descriptor_definitions.h"
#include "raspberryusb_globals.h"


// report descriptor values
// main items
// input
#define RUSB_M_IN_DATA           (uint8_t) (0 << 0)
#define RUSB_M_IN_CONSTANT       (uint8_t) (1 << 0)
#define RUSB_M_IN_ARRAY          (uint8_t) (0 << 1)
#define RUSB_M_IN_VARIABLE       (uint8_t) (1 << 1)
#define RUSB_M_IN_ABSOLUTE       (uint8_t) (0 << 2)
#define RUSB_M_IN_RELATIVE       (uint8_t) (1 << 2)
#define RUSB_M_IN_NO_WRAP        (uint8_t) (0 << 3)
#define RUSB_M_IN_WRAP           (uint8_t) (1 << 3)
#define RUSB_M_IN_LINEAR         (uint8_t) (0 << 4)
#define RUSB_M_IN_NON_LINEAR     (uint8_t) (1 << 4)
#define RUSB_M_IN_PREFERRED      (uint8_t) (0 << 5)
#define RUSB_M_IN_NO_PREFERRED   (uint8_t) (1 << 5)
#define RUSB_M_IN_NO_NULL_STATE  (uint8_t) (0 << 6)
#define RUSB_M_IN_NULL_STATE     (uint8_t) (1 << 6)
#define RUSB_M_IN_BIT_FIELD      (uint8_t) (0 << 8)
#define RUSB_M_IN_BUFFERED       (uint8_t) (1 << 8)

// output
#define RUSB_M_OU_DATA           (uint8_t) (0 << 0)
#define RUSB_M_OU_CONSTANT       (uint8_t) (1 << 0)
#define RUSB_M_OU_ARRAY          (uint8_t) (0 << 1)
#define RUSB_M_OU_VARIABLE       (uint8_t) (1 << 1)
#define RUSB_M_OU_ABSOLUTE       (uint8_t) (0 << 2)
#define RUSB_M_OU_RELATIVE       (uint8_t) (1 << 2)
#define RUSB_M_OU_NO_WRAP        (uint8_t) (0 << 3)
#define RUSB_M_OU_WRAP           (uint8_t) (1 << 3)
#define RUSB_M_OU_LINEAR         (uint8_t) (0 << 4)
#define RUSB_M_OU_NON_LINEAR     (uint8_t) (1 << 4)
#define RUSB_M_OU_PREFERRED      (uint8_t) (0 << 5)
#define RUSB_M_OU_NO_PREFERRED   (uint8_t) (1 << 5)
#define RUSB_M_OU_NO_NULL_STATE  (uint8_t) (0 << 6)
#define RUSB_M_OU_NULL_STATE     (uint8_t) (1 << 6)
#define RUSB_M_OU_NON_VOLATILE   (uint8_t) (0 << 7)
#define RUSB_M_OU_VOLATILE       (uint8_t) (1 << 7)
#define RUSB_M_OU_BIT_FIELD      (uint8_t) (0 << 8)
#define RUSB_M_OU_BUFFERED       (uint8_t) (1 << 8)

// feature
#define RUSB_M_FE_DATA           (uint8_t) (0 << 0)
#define RUSB_M_FE_CONSTANT       (uint8_t) (1 << 0)
#define RUSB_M_FE_ARRAY          (uint8_t) (0 << 1)
#define RUSB_M_FE_VARIABLE       (uint8_t) (1 << 1)
#define RUSB_M_FE_ABSOLUTE       (uint8_t) (0 << 2)
#define RUSB_M_FE_RELATIVE       (uint8_t) (1 << 2)
#define RUSB_M_FE_NO_WRAP        (uint8_t) (0 << 3)
#define RUSB_M_FE_WRAP           (uint8_t) (1 << 3)
#define RUSB_M_FE_LINEAR         (uint8_t) (0 << 4)
#define RUSB_M_FE_NON_LINEAR     (uint8_t) (1 << 4)
#define RUSB_M_FE_PREFERRED      (uint8_t) (0 << 5)
#define RUSB_M_FE_NO_PREFERRED   (uint8_t) (1 << 5)
#define RUSB_M_FE_NO_NULL_STATE  (uint8_t) (0 << 6)
#define RUSB_M_FE_NULL_STATE     (uint8_t) (1 << 6)
#define RUSB_M_FE_NON_VOLATILE   (uint8_t) (0 << 7)
#define RUSB_M_FE_VOLATILE       (uint8_t) (1 << 7)
#define RUSB_M_FE_BIT_FIELD      (uint8_t) (0 << 8)
#define RUSB_M_FE_BUFFERED       (uint8_t) (1 << 8)

// collection
#define RUSB_M_CO_PHYSICAL       (uint8_t) 0x00
#define RUSB_M_CO_APPLICATION    (uint8_t) 0x01
#define RUSB_M_CO_LOGICAL        (uint8_t) 0x02
#define RUSB_M_CO_REPORT         (uint8_t) 0x03
#define RUSB_M_CO_NAMED_ARRAY    (uint8_t) 0x04
#define RUSB_M_CO_USAGE_SWITCH   (uint8_t) 0x05
#define RUSB_M_CO_USAGE_MODIFIER (uint8_t) 0x06

// end collection
#define RUSB_M_END_COLLECTION    (uint8_t) ((1 << 7) | (1 << 6))


// global items
#define RUSB_G_USAGE_PAGE        (uint8_t) (1 << 2)
#define RUSB_G_LOGICAL_MIN       (uint8_t) ((1 << 4) | (1 << 2))
#define RUSB_G_LOGICAL_MAX       (uint8_t) ((1 << 5) | (1 << 2))
#define RUSB_G_PHYSICAL_MIN      (uint8_t) ((1 << 5) | (1 << 4) | (1 << 2))
#define RUSB_G_PHYSICAL_MAX      (uint8_t) ((1 << 6) | (1 << 2))
#define RUSB_G_UNIT_EXPONENT     (uint8_t) ((1 << 6) | (1 << 4) | (1 << 2))
#define RUSB_G_UNIT              (uint8_t) ((1 << 6) | (1 << 5) | (1 << 2))
#define RUSB_G_REPORT_SIZE       (uint8_t) ((1 << 6) | (1 << 5) | (1 << 4) | (1 << 2))
#define RUSB_G_REPORT_ID         (uint8_t) ((1 << 7) | (1 << 2))
#define RUSB_G_REPORT_COUNT      (uint8_t) ((1 << 7) | (1 << 4) | (1 << 2))
#define RUSB_G_PUSH              (uint8_t) ((1 << 7) | (1 << 5) | (1 << 2))
#define RUSB_G_POP               (uint8_t) ((1 << 7) | (1 << 5) | (1 << 4) | (1 << 2))


// local items
#define RUSB_L_USAGE             (uint8_t) ((1 << 3))
#define RUSB_L_USAGE_MIN         (uint8_t) ((1 << 4) | (1 << 3))
#define RUSB_L_USAGE_MAX         (uint8_t) ((1 << 5) | (1 << 3))
#define RUSB_L_DESIG_INDEX       (uint8_t) ((1 << 5) | (1 << 4) | (1 << 3))
#define RUSB_L_DESIG_MIN         (uint8_t) ((1 << 6) | (1 << 3))
#define RUSB_L_DESIG_MAX         (uint8_t) ((1 << 6) | (1 << 4) | (1 << 3))
#define RUSB_L_STR_INDEX         (uint8_t) ((1 << 6) | (1 << 5) | (1 << 4) | (1 << 3))
#define RUSB_L_STR_MIN           (uint8_t) ((1 << 7) | (1 << 3))
#define RUSB_L_STR_MAX           (uint8_t) ((1 << 7) | (1 << 4) | (1 << 3))
#define RUSB_L_DELIMITER         (uint8_t) ((1 << 7) | (1 << 5) | (1 << 3))


// descriptor values
#define RUSB_DEVICE_DESCRIPTOR_BDEVICECLASS         (uint8_t) 0
#define RUSB_DEVICE_DESCRIPTOR_BDEVICESUBCLASS      (uint8_t) 1
#define RUSB_DEVICE_DESCRIPTOR_BDEVICEPROTOCOL      (uint8_t) 2
#define RUSB_DEVICE_DESCRIPTOR_IDVENDOR             (uint8_t) 3
#define RUSB_DEVICE_DESCRIPTOR_IDPRODUCT            (uint8_t) 4
#define RUSB_DEVICE_DESCRIPTOR_BCDDEVICE            (uint8_t) 5
#define RUSB_DEVICE_DESCRIPTOR_IMANUFACTURER        (uint8_t) 6
#define RUSB_DEVICE_DESCRIPTOR_IPRODUCT             (uint8_t) 7
#define RUSB_DEVICE_DESCRIPTOR_ISERIALNUMBER        (uint8_t) 8

#define RUSB_CONFIGURATION_DESCRIPTOR_WTOTALLENGTH      (uint8_t) 0
#define RUSB_CONFIGURATION_DESCRIPTOR_BNUMINTERFACES    (uint8_t) 1
#define RUSB_CONFIGURATION_DESCRIPTOR_BMATTRIBUTES      (uint8_t) 2
#define RUSB_CONFIGURATION_DESCRIPTOR_MAXPOWER          (uint8_t) 3

#define RUSB_INTERFACE_DESCRIPTOR_BINTERFACENUMBER      (uint8_t) 0
#define RUSB_INTERFACE_DESCRIPTOR_BALTERNATESETTING     (uint8_t) 1
#define RUSB_INTERFACE_DESCRIPTOR_BNUMENDPOINTS         (uint8_t) 2
#define RUSB_INTERFACE_DESCRIPTOR_BINTERFACECLASS       (uint8_t) 3
#define RUSB_INTERFACE_DESCRIPTOR_BINTERFACESUBCLASS    (uint8_t) 4
#define RUSB_INTERFACE_DESCRIPTOR_BINTERFACEPROTOCOL    (uint8_t) 5
#define RUSB_INTERFACE_DESCRIPTOR_IINTERFACE            (uint8_t) 6

#define RUSB_ENDPOINT_DESCRIPTOR_BENDPOINTADDRESS   (uint8_t) 0
#define RUSB_ENDPOINT_DESCRIPTOR_BMATTRIBUTES       (uint8_t) 1
#define RUSB_ENDPOINT_DESCRIPTOR_WMAXPACKETSIZE     (uint8_t) 2
#define RUSB_ENDPOINT_DESCRIPTOR_BINTERVAL          (uint8_t) 3

#define RUSB_HID_DESCRIPTOR_BCOUNTRYCODE            (uint8_t) 0
#define RUSB_HID_DESCRIPTOR_BNUMDESCRIPTORS         (uint8_t) 1
#define RUSB_HID_DESCRIPTOR_BDESCRIPTORTYPE         (uint8_t) 2
#define RUSB_HID_DESCRIPTOR_WDESCRIPTORLENGTH       (uint8_t) 3


// descriptor-generation functions
void rusb_generate_all_descriptors();
void rusb_generate_device_descriptor(rusb_device_descriptor* descriptor);
void rusb_generate_configuration_descriptor(rusb_configuration_descriptor* descriptor);
void rusb_generate_interface_descriptor(rusb_interface_descriptor* descriptor);
void rusb_generate_endpoint_descriptor(rusb_endpoint_descriptor* descriptor);
void rusb_generate_hid_descriptor(rusb_hid_descriptor* descriptor);

// descriptor value setter functions
void rusb_device_descriptor_set(uint8_t field, rusb_device_descriptor* descriptor, uint16_t value);
void rusb_configuration_descriptor_set(uint8_t field, rusb_configuration_descriptor* descriptor, uint16_t value);
void rusb_interface_descriptor_set(uint8_t field, rusb_interface_descriptor* descriptor, uint16_t value);
void rusb_endpoint_descriptor_set(uint8_t field, rusb_endpoint_descriptor* descriptor, uint16_t value);
void rusb_hid_descriptor_set(uint8_t field, rusb_hid_descriptor* descriptor, uint16_t value);

// report & string descriptor functions
void rusb_set_report_descriptor(const uint8_t *extern_descriptor);
void rusb_set_string_descriptor_manufacturer(const uint8_t *extern_descriptor);
void rusb_set_string_descriptor_product(const uint8_t *extern_descriptor);
void rusb_set_string_descriptor_serial_number(const uint8_t *extern_descriptor);


#endif
