#ifndef RASPBERRYUSB_GLOBALS_H
#define RASPBERRYUSB_GLOBALS_H


typedef enum {
    None, Default, Addressed, Configured, Suspended
} rusb_USB_state;

typedef enum {
    None, Trans_complete, Trans_done, Stall_sent, Data_seq_error, Error
} rusb_packet_responses_out;


extern rusb_USB_state global_USB_state;
extern rusb_packet_responses_out global_packet_response_out;


#endif
