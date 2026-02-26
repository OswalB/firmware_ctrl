#pragma once
#include <stdint.h>
#include "core/types/token_types.h"

typedef struct
{
    uint8_t     length;
    TokenClass  pattern[5];
} GrammarRule;