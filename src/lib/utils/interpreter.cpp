#include <stddef.h>
#include <Arduino.h>

#include "interpreter.h"


const char* enum_to_string(
    const EnumEntry *table,
    size_t count,
    int value)
{
    for (size_t i = 0; i < count; i++)
    {
        if (table[i].value == value)
            return table[i].name;
    }

    return "?";
}

int enum_from_string(
    const EnumEntry *table,
    size_t count,
    const char *str)
{
    for (size_t i = 0; i < count; i++)
    {
        if (strcasecmp(str, table[i].name) == 0)
            return table[i].value;
    }

    return -1;
}