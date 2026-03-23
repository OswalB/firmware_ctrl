#pragma once

#include "menu_types.h"
#include "core/model/param_types.h"

#define MENU_MAX_VISIBLE 4
#define MENU_MAX_DEPTH   3
#define MENU_LINE_LEN 32

extern bool menu_dirty;

typedef struct
{
    uint8_t count;
    char lines[MENU_MAX_VISIBLE][MENU_LINE_LEN];
    uint8_t cursor;
} MenuView;

typedef int32_t (*ParamGetter)(uint8_t id);

typedef struct
{
    ParamGetter getters[PARAM_COUNT];
} DomainAccess;


void menu_init(void);
void menu_update(void);

void menu_input(MenuInputEvent ev);

void menu_render(MenuView *view);
MenuState menu_get_state();


