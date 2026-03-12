#pragma once

#include <stdint.h>

typedef enum
{
    MENU_ITEM_SUBMENU,
    MENU_ITEM_COMMAND,
    MENU_ITEM_VALUE,
    MENU_ITEM_BACK
} MenuItemType;

typedef enum
{
    MENU_HOME,
    MENU_NAV,
    MENU_EDIT
} MenuState;

typedef enum
{
    MENU_UP,
    MENU_DOWN,
    MENU_ENTER,
    MENU_BACK,
    MENU_INC,
    MENU_DEC,
    MENU_TIMEOUT,
    MENU_OPEN
} MenuInputEvent;

