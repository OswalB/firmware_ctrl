#pragma once
#include "modules/display/display.h"

void lcd_init(void);
void lcd_render(MenuView *view);
void lcd_dashboard_render(void);