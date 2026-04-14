#ifndef RASPBERRYUSB_GLOBALS_H
#define RASPBERRYUSB_GLOBALS_H


typedef enum {
    None, Default, Addressed, Configured, Suspended
} rusb_USB_state;

typedef enum {
    None, Trans_complete, Trans_done, Stall, Nak, Data_seq_error, Error
} rusb_packet_response_out;

typedef enum {
    None, Trans, Stall, Nak
} rusb_packet_response_in;


extern volatile rusb_USB_state global_USB_state;
extern volatile rusb_packet_response_out global_packet_response_out;
extern volatile rusb_packet_response_in global_packet_response_in;
extern volatile uint8_t global_buffer_status[2][16];

#endif
