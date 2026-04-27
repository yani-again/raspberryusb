#include "raspberryusb_globals.h"
#include "raspberryusb_descriptors.h"


// supported descriptors:
// device, configuration, string, interface, endpoint, HID, and report
const uint8_t rusb_supported_descriptors[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x21, 0x22};
const uint8_t rusb_supported_descriptors_count =
        sizeof(rusb_supported_descriptors) / sizeof(rusb_supported_descriptors[0]);

volatile rusb_USB_state global_USB_state = State_None;
volatile rusb_packet_response_out global_packet_response_out = Out_None;
volatile rusb_packet_response_in global_packet_response_in = In_None;
volatile uint8_t global_buffer_status[2][16] = {0};
uint8_t rusb_ep0_pid = 1;

rusb_device_descriptor device_descriptor;
rusb_configuration_descriptor configuration_descriptor;
rusb_interface_descriptor interface_descriptor;
rusb_endpoint_descriptor endpoint_descriptor_1_in;
rusb_endpoint_descriptor endpoint_descriptor_1_out;
rusb_hid_descriptor hid_descriptor;

// report & string descriptors
const uint8_t *rusb_report_descriptor;
const uint8_t *rusb_string_descriptor_manufacturer;
const uint8_t *rusb_string_descriptor_product;
const uint8_t *rusb_string_descriptor_serial_number;

