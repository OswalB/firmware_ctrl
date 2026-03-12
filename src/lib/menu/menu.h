#pragma once

#include "menu_types.h"

#define MENU_MAX_VISIBLE 4
#define MENU_MAX_DEPTH   3

typedef struct
{
    uint8_t count;
    const char *lines[MENU_MAX_VISIBLE];
    uint8_t cursor;
} MenuView;

void menu_init(void);

void menu_input(MenuInputEvent ev);

void menu_render(MenuView *view);

