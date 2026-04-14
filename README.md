# RaspberryUSB
*RP2040 USB Device Drivers*

## About
Low-level USB device drivers for HID devices using the RP2040, implemented with no external libraries and designed to expose a large portion of the behaviour of the hardware USB controller.

The goal of RaspberryUSB is to be an abstraction layer between the hardware and software, allowing for a plug-and-play implementation of the USB protocol without reliance on bloated libraries.

Since it's HID-focused, this means implementation is only supported for HID devices (e.g. keyboard, mouse, gamepad).

As an unintended side-effect of the minimal approach, this is also a memory-safe USB implementation (no `malloc`)

## Motivation
Because the RP2040 is very limited on resources, the general functionality provided by libraries like [TinyUSB](https://github.com/hathach/tinyusb) can become noticeably bloated. While excellent production tools, they are (by nature) not as lean as some projects demand.

This is where RasberryUSB fits in.

As further motivation, USB is often treated as a black box. Large libraries make it trivial to use but don't let you understand what's happening under the surface.

RaspberryUSB tries its best to expose the inner workings of USB just enough to require a basic understanding of how USB works (for the learning experience), however it doesn't expect a level of technical knowledge anywhere near the likes of knowing the USB specification inside-out.

## Features
- Minimal USB device stack for the RP2040
- Follows the USB 2.0 specification
- HID device support (keyboard, mouse, gamepad)
- Full-speed USB (12 Mbps)
- Interrupt and endpoint support
    - Only control and interrupt endpoints supported currently
- Composite device support
- Lightweight, minimally abstracted driver-style API
- Designed to be a low-resource device USB implementation that aids with learning how USB works
- Memory safe (no `malloc`)

### Key Functionalities
- Provide easily digestible functions that require minimal USB specification knowledge to work with
- Directly handle enumeration and data transfers
- Provide a simple-to-use API for descriptor/endpoint configuration, IN/OUT transfer data buffers, and interrupt handling

## Getting Started

### Requirements
- RP2040 microcontroller
- C toolchain (ARM GCC)
- Basic knowledge of USB HID descriptors

### Installation
**TODO:** finish this once a working version is released

## API Overview

### Important Functions
```c
// same process for all descriptors
struct raspberryusb_device_descriptor device_descriptor = generate_device_descriptor();

device_descriptor.vendor_id  =  0x1234;
device_descriptor.product_id =  0x5678;
device_descriptor.device_type = DEVICE_DESCRIPTOR_KEYBOARD;


// initialisation & (automatic) enumeration
initialise_single_device(device_descriptor, ...);

// or
initialise_composite_device(struct raspberryusb_device_descriptor* device_descriptors);


// receiving data (defining interrupts)
// using function define_receive_isr(void (*isr)(void), int index)
void receive_isr_1(void);
void receive_isr_2(void);

define_receive_isr(receive_isr_1, 0);
define_receive_isr(receive_isr_2, 1);


// sending data
// TODO: uncertain how this will work yet
```

### Keyboard Enumeration Example
```c
// TODO: write keyboard enumeration code
```

## System Context
High-level overview of the driver's role in context to hardware/application layers.
```
┌─────────────────────────────┐
│        Application          │
├─────────────────────────────┤
│ Configure descriptors       │
│ Configure endpoints         │
│ Supply data for endpoints   │
│ Handle USB events           │
└─────────────▲───────────────┘
              │ API calls
┌─────────────┴───────────────┐
│        RaspberryUSB         │
├─────────────────────────────┤
│ Enumeration handling        │
│ Control transfers (EP0)     │
│ Descriptor management       │
│ Data transfer management    │
└─────────────▲───────────────┘
              │  USB engine
┌─────────────┴───────────────┐
│    RP2040 USB Controller    │
├─────────────────────────────┤
│ Endpoint buffers            │
│ CRC generation/check        │
│ Packet encoding/decoding    │
│ USB interrupts              │
└─────────────▲───────────────┘
              │  USB Bus
┌─────────────┴───────────────┐
│       USB Host Device       │
│     (Windows/Mac/Linux)     │
└─────────────────────────────┘
```

## Architecture
```
┌─── usb_descriptors.c
│    all descriptors
│
├─── usb_hw.c
│    USB controller interaction
│
├─── usb_ep.c
│    endpoint configuration and buffer management
│
├─── usb_control.c
│    control transfer handling
│
└─── usb.c
     public driver interface
```

## Limitations
No support for:
- Isochronous and bulk transfer support
- Non-HID devices
- Devices with multiple configurations
- Remote wakeup and suspend states
- Physical descriptor (only used in super-niche HID devices, though it can easily be added on your own)
- "Long" items within the report descriptor (largely unnecessary for HID devices, however as above, it can be easily added should it be needed)
- Double-buffered transfer modes
- EP0 only uses 1 data buffer, the optional one at offset 0x140 is left unused

## Constraints
The RP2040's hardware USB controller poses several limitations for device-mode, the most notable being:
- Full-speed only (12 Mbps)
- Limited endpoint buffer memory (60 x 64-byte buffers)

## Non-Goals
***Currently,*** this project intentionally does ***not*** attempt to:
- replicate full production USB implementations
- support every USB device class
- support MCU's beyond the RP2040
- provide a high-level USB framework with extreme abstractions

## Future Improvements
Possible extensions could be:
- CDC or mass-storage class implementation
- integration with embedded RTOS-es
- higher-level abstractions
- support for an additional MCU

## License
Copyright © 2026 Yanislav Yankov

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
