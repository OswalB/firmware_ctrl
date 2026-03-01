#pragma once

#include "core/model/token_types.h"

#include <stdint.h>
#include <stdbool.h>

uint8_t classify_tokens(
    char raw_tokens[][32],
    int token_count,
    Token *out_tokens);
