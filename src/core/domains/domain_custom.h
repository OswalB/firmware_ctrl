#pragma once

#include "core/model/event_types.h"

void machine_custom_handle(const Event& evt);
typedef void (*CustomHandler)(const Event& evt);

typedef struct
{
    EventType type;
    ParamType param;
    CustomHandler handler;
} CustomCommandEntry;