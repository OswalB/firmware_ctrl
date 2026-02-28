#pragma once

#include "core/types/token_types.h"

#include <stdint.h>
#include <stdbool.h>
// #include "token.h"
#include "core/types/token_types.h"

uint8_t classify_tokens(
    char raw_tokens[][32],
    int token_count,
    Token *out_tokens);
