#pragma once

#include <avr/pgmspace.h>
#include "menu_types.h"

typedef struct
{
    uint8_t id;
    uint8_t parent;
    MenuItemType type;
    const char *label;
} MenuItem;

extern const MenuItem menu_table[];
extern const uint8_t menu_table_size;
