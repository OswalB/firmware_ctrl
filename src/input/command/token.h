#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "core/types/event_types.h"
#include "core/types/domain_types.h"
#include "core/types/param_types.h"

typedef enum
{
    TOKEN_UNKNOWN = 0,
    TOKEN_CMD,
    TOKEN_DOMAIN,
    TOKEN_PARAM,
    TOKEN_NUMBER
} TokenType;

typedef struct
{
    TokenType type;

    union
    {
        EventType  cmd;
        DomainType domain;
        ParamType  param;
        int32_t    number;
    };

} Token;

