#include "raspberryusb_globals.h"


volatile rusb_USB_state global_USB_state = None;
volatile rusb_packet_response_out global_packet_response_out = None;
volatile rusb_packet_response_in global_packet_response_in = None;
volatile uint8_t global_buffer_status[2][16] = {0};

