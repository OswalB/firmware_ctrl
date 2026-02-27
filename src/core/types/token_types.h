#pragma once

typedef enum
{
    TK_UNKNOWN = 0,
    TK_CMD,
    TK_DOMAIN,
    TK_ID,
    TK_PARAM,
    TK_VALUE,
    TK_COUNT
} TokenClass;