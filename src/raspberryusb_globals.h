#ifndef RASPBERRYUSB_GLOBALS_H
#define RASPBERRYUSB_GLOBALS_H


#include "raspberryusb_descriptor_definitions.h"


typedef enum {
    State_None, State_Default, State_Addressed, State_Configured, State_Suspended
} rusb_USB_state;

typedef enum {
    Out_None, Out_Trans_complete, Out_Trans_done, Out_Stall,
	Out_Nak, Out_Data_seq_error, Out_Error
} rusb_packet_response_out;

typedef enum {
    In_None, In_Trans, In_Trans_done, In_Stall, In_Nak
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
