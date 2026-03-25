#pragma once

#include <stdint.h>
#include "lib/menu/menu.h"
#define LCD_COLS 20
#define LCD_ROWS 4



void display_init(void);
void display_render(MenuView *view);

