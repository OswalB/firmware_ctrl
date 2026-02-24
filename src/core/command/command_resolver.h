#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "core/types/domain_types.h"
#include "core/types/event_types.h"
#include "core/types/param_types.h"

#define MAX_PARAMS 4

typedef struct
{
    EventType type;
    DomainType domain;
    uint8_t id;
    ParamType param;
    int32_t value;
} CommandMatch;

bool command_resolve(
    char tokens[][32],
    int token_count,
    CommandMatch *out_match);