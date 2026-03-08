#pragma once

#include "core/model/event_types.h"

void machine_led_handle(const Event& evt);
typedef void (*LedHandler)(const Event& evt);

typedef struct
{
    EventType type;
    ParamType param;
    LedHandler handler;
} LedCommandEntry;