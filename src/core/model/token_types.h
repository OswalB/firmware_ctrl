#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "core/model/event_types.h"
#include "core/model/domain_types.h"
#include "core/model/param_types.h"

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



typedef enum
{
    TK_CMD = 0,
    TK_DOMAIN,
    TK_PARAM,
    TK_NUMBER,
    TK_INVALID
} TokenClass;

