#pragma once

#include "menu_types.h"

#define MENU_MAX_VISIBLE 4
#define MENU_MAX_DEPTH   3
#define MENU_LINE_LEN 32

typedef struct
{
    uint8_t count;
    char lines[MENU_MAX_VISIBLE][MENU_LINE_LEN];
    uint8_t cursor;
} MenuView;

void menu_init(void);

void menu_input(MenuInputEvent ev);

void menu_render(MenuView *view);
MenuState menu_get_state();

