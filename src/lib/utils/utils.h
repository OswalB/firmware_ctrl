#pragma once

#include <stdbool.h>

/*==================================================
                 STRINGS
====================================================*/
bool utils_is_numeric(const char *str);
void utils_to_uppercase(char *str);

/*==================================================
                 CONVERT
====================================================*/

bool utils_parse_long(const char *token, long *out);
const char* enum_toString(int value,
                          const char* const table[],
                          int count);