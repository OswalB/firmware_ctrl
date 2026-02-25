#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "core/types/event_types.h"

#define EVENT_QUEUE_SIZE 10

typedef struct
{
    Event buffer[EVENT_QUEUE_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t count;
} EventQueue;

void eventQueue_init(void);
bool eventQueue_push(Event evt);
bool eventQueue_pop(Event *evt);
bool eventQueue_isEmpty(void);