#ifndef RASPBERRYUSB_GLOBALS_H
#define RASPBERRYUSB_GLOBALS_H


#include "raspberryusb_descriptors.h"


typedef enum {
    None, Default, Addressed, Configured, Suspended
} rusb_USB_state;

typedef enum {
    None, Trans_complete, Trans_done, Stall, Nak, Data_seq_error, Error
} rusb_packet_response_out;

typedef enum {
    None, Trans, Stall, Nak
} rusb_packet_response_in;


extern const uint8_t rusb_supported_descriptors[];

extern volatile rusb_USB_state global_USB_state;
extern volatile rusb_packet_response_out global_packet_response_out;
extern volatile rusb_packet_response_in global_packet_response_in;
extern volatile uint8_t global_buffer_status[2][16];

extern rusb_device_descriptor device_descriptor;
extern rusb_configuration_descriptor configuration_descriptor;
extern rusb_interface_descriptor interface_descriptor;
extern rusb_endpoint_descriptor endpoint_descriptor_1_in;
extern rusb_endpoint_descriptor endpoint_descriptor_1_out;
extern rusb_hid_descriptor hid_descriptor;

extern const uint8_t *rusb_report_descriptor;
extern const uint8_t *rusb_string_descriptor_manufacturer;
extern const uint8_t *rusb_string_descriptor_product;
extern const uint8_t *rusb_string_descriptor_serial_number;


#endif
