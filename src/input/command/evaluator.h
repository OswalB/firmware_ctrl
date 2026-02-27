#pragma once

#include "core/types/token_types.h"
#include "input/command/token.h"

//bool match_grammar(TokenClass types[], uint8_t count);
bool evaluate_command(Token *tokens, int token_count, Event *out);