## Enumeration

### Setup Packet
Once the interrupt handler detects an interrupt for the setup packet being received, it sets `global_USB_state` to `Default`. As the enum variable is declared as `volatile`, the programmer can wait for the setup packet to be received using a loop as follows:
```c
// wait for USB state to be updated, signaling setup packet being received
while (global_USB_state != Default)
    ;
```

## Sending/Receiving Packets

### Interrupt Service Routine (ISR)
The interrupt handler checks for completed buffers. That's it. It's up to the programmer to ensure they're handling the correct endpoint by checking `global_buffer_status`. It has the following structure:
- 2D array
- size 2 x 16
- global_buffer_status[0] = OUT endpoints
- global_buffer_status[1] = IN endpoints
- global_buffer_status[X][0-15] = specific endpoint
It is initialised as all zeroes, a bit is set once a buffer is completed.

> [!WARNING]
> It's important that you as the programmer clear the set bit within `global_buffer_status` once done checking, as it is not automatically cleared.

It takes the endpoint number as a parameter. It returns one of the following values from the `rusb_packet_responses_out` enum:
- `Trans_complete` when the transaction is complete and the last packet has been received
- `Trans_done` when the transaction is complete but the packet received was not the last packet
- `Stall_sent` when the endpoint responded with a STALL to the OUT packet
- `Stall_received` when the OUT packet is a STALL
- `Data_seq_error` when there was a data sequence error
- `Error` when there was any other error

### Packet Handling
The interrupts for `INTS.BUFF_STATUS` and `INTS.TRANS_COMPLETE` are handled by the interrupt handler as follows:
- check which direction the interrupt occurred for
- check which endpoint the interrupt occurred for
- set the correct value within the correct enum between `global_packet_response_out` or `global_packet_response_in`
- write to `global_buffer_status`
- clear `INTS.TRANS_COMPLETE` (if necessary)
- clear `BUFF_STATUS`

### Global Data Structures
`global_buffer_status`, `global_packet_response_out` and `global_packet_response_in` are used to aid the programmer with important details. `global_buffer_status` is a 2D array of *uint8_t*, the latter two are enum data types.

#### `global_buffer_status`
This one specifies which endpoint & direction the most recent buffer completed on. Further details are below in the **Interrupt Service Routine (ISR)** section.

#### `global_packet_response_out`
It can take one of the following values
- `Trans_complete` when the transaction is complete and the last packet has been received
- `Trans_done` when the transaction is complete but the packet received was not the last packet of the transaction
- `Stall_sent` when the endpoint responded with a STALL to the OUT packet
- `Stall_received` when the OUT packet is a STALL
- `Data_seq_error` when there was a data sequence error
- `Error` when there was any other error

The `rusb_transfer_handler_out(uint8_t ep_num)` is the provided function call for handling OUT packets.

It takes the endpoint number as a parameter. It returns one of the following values from the `rusb_packet_responses_out` enum:
- `Trans_complete` when the transaction is complete and the last packet has been received
- `Trans_done` when the transaction is complete but the packet received was not the last packet
- `Stall_sent` when the endpoint responded with a STALL to the OUT packet
- `Stall_received` when the OUT packet is a STALL
- `Data_seq_error` when there was a data sequence error
- `Error` when there was any other error

> [!NOTE]
> `rusb_packet_responses_out` can also have the value `None`, however that should never happen under normal circumstances and is only used as an initial value, so no checks exist for it anywhere.

### Errors
Currently, all packet-related errors are bundled into 1 `if` statement that causes the buffer bit to be flipped and the function to terminate early. It also sets the `global_packet_response_in` or `global_packet_response_out` to be set to `Error` - so it's ambiguous but open to improvements in the future. Here is an example of the code for OUT transfers:
```c
if (RUSB_SIE_STATUS & (RUSB_SIE_STATUS_DATA_SEQ_ERROR |
                        RUSB_SIE_STATUS_NAK_REC |
                        RUSB_SIE_STATUS_RX_TIMEOUT |
                        RUSB_SIE_STATUS_RX_OVERFLOW |
                        RUSB_SIE_STATUS_BIT_STUFF_ERROR |
                        RUSB_SIE_STATUS_CRC_ERROR))
{
    if (RUSB_SIE_STATUS & RUSB_SIE_STATUS_DATA_SEQ_ERROR)
    {
        global_packet_response_out = Data_seq_error;
    }
    else
    {
        global_packet_response_out = Error;
    }

    RUSB_SIE_STATUS &= (~RUSB_SIE_STATUS_DATA_SEQ_ERROR &
                        ~RUSB_SIE_STATUS_NAK_REC &
                        ~RUSB_SIE_STATUS_RX_TIMEOUT &
                        ~RUSB_SIE_STATUS_RX_OVERFLOW &
                        ~RUSB_SIE_STATUS_BIT_STUFF_ERROR &
                        ~RUSB_SIE_STATUS_CRC_ERROR);

    RUSB_BUFF_STATUS &= ~RUSB_BUFF_STATUS_EP_OUT(ep_num);

    return;
}
```

> [!NOTE]
> The only exception is the `SIE_STATUS.DATA_SEQ_ERROR` bit, which is checked separately and, if set, sets `global_packet_response_out` to `Data_seq_error`.
> 
> This likely doesn't offer many advantages, but the RP2040 datasheet singles that error check out. There are likely use cases for it I am not aware, hence its implementation into RaspberryUSB.

### Miscellaneous

#### Host Suspend
RaspberryUSB sets `global_USB_state` to `Suspended` when the host suspends the device.

There are no checks within RaspberryUSB's code in regards to the USB state, so it's up to the programmer to ensure they do not attempt anything when the state is set to `Suspended`.

*The implementation is like this in order to stay true to RaspberryUSB being a minimal USB driver that does very little hand-holding.*

#### Macro Limitations
When using the following macros:
```c
#define RUSB_DPSRAM_EP_IN_CTRL(ep_num)      (*(volatile uint32_t *) \
                                              (RUSB_USBCTRL_REGS_BASE + (ep_num * 8)))
#define RUSB_DPSRAM_EP_OUT_CTRL(ep_num)     (*(volatile uint32_t *) \
                                              (RUSB_USBCTRL_REGS_BASE + (ep_num * 8) + 4))
#define RUSB_BUFF_STATUS_EP_IN(ep_num)  (uint32_t) (1 << (2 * ep_num))
#define RUSB_BUFF_STATUS_EP_OUT(ep_num) (uint32_t) (1 << (2 * ep_num + 1))
```
Ensure that ep\_num is **less than or equal to** 15.

## Creating Descriptors

### Declaring
Descriptor structs available to use for descriptor declaration:
- `rusb_device_descriptor`
- `rusb_configuration_descriptor`
- `rusb_interface_descriptor`
- `rusb_endpoint_descriptor`
- `rusb_hid_descriptor`

Example declarations:
```c
rusb_device_descriptor device_descriptor;
rusb_configuration_descriptor configuration_descriptor;
```

Descriptor initialisation is **discouraged**, use the functions below instead. The exception is the string descriptor as that would require `malloc` to reasonably implement.

### Descriptor Initialisation
Declared descriptors can be initialised using initialisation functions, which simply set default values:
- `void generate_device_descriptor(rusb_device_descriptor* descriptor)`
- `void generate_configuration_descriptor(rusb_configuration_descriptor* descriptor)`
- `void generate_interface_descriptor(rusb_interface_descriptor* descriptor)`
- `void generate_endpoint_descriptor(rusb_endpoint_descriptor* descriptor)`
- `void generate_hid_descriptor(rusb_hid_descriptor* descriptor)`

#### Default Values
Complete list of what every descriptor type looks after default initialisation, **all are little-endian.**

##### Device Descriptor
```c
uint8_t  bLength            = 0x12
uint8_t  bDescriptorType    = 0x01
uint16_t bcdUSB             = 0x0002
uint8_t  bDeviceClass       = 0x00
uint8_t  bDeviceSubclass    = 0x00
uint8_t  bDeviceProtocol    = 0x00
uint8_t  bMaxPacketSize0    = 0x40
uint16_t idVendor           = 0x0000
uint16_t idProduct          = 0x0000
uint16_t bcdDevice          = 0x0100
uint8_t  iManufacturer      = 0x00
uint8_t  iProduct           = 0x01
uint8_t  iSerialNumber      = 0x02
uint8_t  bNumConfigurations = 0x01
```

##### Configuration Descriptor
```c
uint8_t  bLength                = 0x09
uint8_t  bDescriptorType        = 0x02
uint16_t wTotalLength           = 0x0000
uint8_t  bNumInterfaces         = 0x01
uint8_t  bConfigurationValue    = 0x01
uint8_t  iConfiguration         = 0x03
uint8_t  bmAttributes           = 0x00
uint8_t  MaxPower               = 0x00
```

##### Interface Descriptor
```c
uint8_t  bLength            = 0x09
uint8_t  bDescriptorType    = 0x04
uint8_t  bInterfaceNumber   = 0x00
uint8_t  bAlternateSetting  = 0x00
uint8_t  bNumEndpoints      = 0x00
uint8_t  bInterfaceClass    = 0x03
uint8_t  bInterfaceSubClass = 0x00
uint8_t  bInterfaceProtocol = 0x00
uint8_t  iInterface         = 0x04
```

##### Endpoint Descriptor
```c
uint8_t  bLength            = 0x07
uint8_t  bDescriptorType    = 0x05
uint8_t  bEndpointAddress   = 0x00
uint8_t  bmAttributes       = 0x00
uint16_t wMaxPacketSize     = 0x0000
uint8_t  bInterval          = 0x00
```

##### HID Descriptor
```c
uint8_t  bLength = 0x09;
uint8_t  bDescriptorType = 0x21;
uint16_t bcdHID = 0x1011;
uint8_t  bCountryCode = 0x00;
uint8_t  bNumDescriptors = 0x01;
uint8_t  bDescriptorType = 0x22;
uint16_t wDescriptorLength = 0x0000;
```
> [!NOTE]
> Although the physical descriptor is not supported by RaspberryUSB, you can simply define your own HID descriptor and include it there as additional `bDescriptorType` and `wDescriptorLength` fields.
> 
> Then, simply define your own physical descriptor and send it through during enumeration.

When generating a device descriptor using `generate_device_descriptor()`:
- bDeviceClass, bDeviceSubClass, and bDeviceProtocol are set to `0x00` by default
- bMaxPacketSize0 is set to `0x40`
- iManufacturer, iProduct, and iSerialNumber are `0x00`

**All of the above default values can be changed by you, example below.**
```c
// declare
rusb_configuration_descriptor configuration_descriptor;
// initialise with default values
generate_configuration_descriptor(&configuration_descriptor);

// set a specific field
device_descriptor->MaxPower = 0xFA;
```

### The Report Descriptor
This is probably the most confusing part from the whole USB HID specification (at least personally).

In short, every main item in the report descriptor needs *at least* these:
- input/output/feature
- usage
- usage page
- logical min
- logical max
- report size
- report count

And since the report descriptor size will vary between devices (just like the string descriptor), there are functions to define **fields** within an array of values you should declare yourself. Below is a list of these functions.

#### Report Descriptor Provided Values
- 

