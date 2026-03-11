#pragma once

#include <stddef.h>

typedef struct
{
    const char *name;
    int value;
} EnumEntry;

const char *enum_to_string(const EnumEntry *table, size_t count, int value);
int enum_from_string(const EnumEntry *table, size_t count, const char *str);