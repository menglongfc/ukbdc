#include "usb_config.h"
#include <avr/pgmspace.h>

struct endpoint_config PROGMEM endpoint_configs[NUM_ENDPOINTS] = {
	{.num = 0,
		.type = EP_TYPE_CONTROL,
		.config = EP_SIZE_32 | EP_SINGLE_BUFFER,
		_BV(RXSTPE)},
	{.num = KEYBOARD_ENDPOINT,
		.type = EP_TYPE_INTERRUPT_IN,
		.config = EP_SIZE_32 | EP_DOUBLE_BUFFER,
		.int_flags = 0x00},
	{.num = RAWHID_TX_ENDPOINT,
		.type = EP_TYPE_INTERRUPT_IN,
		.config = EP_SIZE_64 | EP_DOUBLE_BUFFER,
		.int_flags = 0x00},
	{.num = RAWHID_RX_ENDPOINT,
		.type = EP_TYPE_INTERRUPT_OUT,
		.config = EP_SIZE_64 | EP_DOUBLE_BUFFER,
		.int_flags = 0x00}
};

#include "hid.h"
#include "rawhid.h"
struct interface_request_handler iface_req_handlers[] = {
	{.iface_number = KEYBOARD_INTERFACE,
		.f = &HID_handle_control_request},
	/* commented out until the handler works */
	/* {.iface_number = RAWHID_INTERFACE,
		.f = &RAWHID_handle_control_request}, */
	{.iface_number = 0, .f = 0}
};
struct sof_handler sof_handlers[] = {
	{.f = &HID_handle_sof},
	{.f = 0}
};
