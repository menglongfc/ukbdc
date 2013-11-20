#pragma once

#include <stdint.h>
#include "list.h"

#define ERR_WRONG_TYPE -1
#define ANY_SUBTYPE 0xff

typedef void (*task_callback_t)();

typedef struct {
	int priority;
	int last_run;
	task_callback_t callback;
} task_t;

#include "system_messages.h"

typedef void (*message_callback_t)(void *data);

typedef struct {
	uint8_t subtype;
	message_callback_t callback;
} message_handler_t;

void SYSTEM_init();
void SYSTEM_add_task(task_callback_t callback, int priority);
void SYSTEM_main_loop();

/* Notify all the subscribers of message's type and/or subtype */
int SYSTEM_publish_message(message_type_t type, uint8_t subtype, void *data);
/* Subscribe to a particular message type. The subscriber will be called only
 * on a message with specified subtype */
int SYSTEM_subscribe_subtyped(message_type_t type, uint8_t subtype, message_callback_t handler);
/* Subscribe to a particular message type. The subscriber will be called on
 * a message with any subtype. Subtype must be between 0x00 and 0xfe, 0xff
 * means any subtype */
static inline int SYSTEM_subscribe(message_type_t type, message_callback_t callback)
{
	return SYSTEM_subscribe_subtyped(type, ANY_SUBTYPE, callback);
}