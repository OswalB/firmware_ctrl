
#include "display.h"        
#include "drivers/lcd_driver/lcd_driver.h"

void display_init(void)
{
    lcd_init();
}

void display_render(MenuView *view)
{
    lcd_render(view);
}