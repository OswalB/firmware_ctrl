#pragma once

#include <avr/pgmspace.h>
#include "menu_types.h"
#include "core/model/token_types.h"
#include "core/model/domain_types.h"
#include "core/model/event_types.h"

typedef struct
{
    uint8_t id;
    uint8_t parent;
    MenuItemType type;
    const char *label;

    Token tokens[5];
} MenuItem;

extern const MenuItem menu_table[];
extern const uint8_t menu_table_size;
