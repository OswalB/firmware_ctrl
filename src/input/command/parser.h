#pragma once
#include <stdbool.h>
#include "core/model/token_types.h"   // ← necesario

#ifdef __cplusplus
extern "C" {
#endif

// Motor principal reutilizable
bool parser_process_tokens(Token *typed, int token_count);

// Entrada CLI
void parser_parse_line(const char *line);

#ifdef __cplusplus
}
#endif