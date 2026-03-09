#pragma once

#include <Arduino.h>
#include <stdbool.h>

/*==================================================
                 STRINGS
====================================================*/
bool utils_is_numeric(const char *str);
void utils_to_uppercase(char *str);
void utils_strcopy_safe(char *dst, const char *src, size_t size);

/*==================================================
                 CONVERT
====================================================*/

bool utils_parse_long(const char *token, long *out);
const char* enum_toString(int value,
                          const char* const table[],
                          int count);