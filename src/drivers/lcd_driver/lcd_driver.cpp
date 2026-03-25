
#include "lcd_driver.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

static LiquidCrystal_I2C lcd(0x27, 20, 4);

// buffer anterior para evitar redibujar todo
static char last_lines[LCD_ROWS][LCD_COLS + 1];
static uint8_t last_cursor = 255;

// buffer temporal de línea formateada
static char render_line[LCD_COLS + 1];

void lcd_init(void)
{
    lcd.init();
    lcd.backlight();
    lcd.clear();

    // limpiar buffers
    for (uint8_t i = 0; i < LCD_ROWS; i++)
    {
        memset(last_lines[i], 0, sizeof(last_lines[i]));
    }
}

static void format_line(MenuView *view, uint8_t i)
{
    memset(render_line, ' ', LCD_COLS);
    render_line[LCD_COLS] = '\0';

    if (i >= view->count)
        return;

    // cursor
    if (i == view->cursor)
        render_line[0] = '>';
    else
        render_line[0] = ' ';

    // copiar texto (desde posición 1)
    strncpy(&render_line[1], view->lines[i], LCD_COLS - 1);
}

void lcd_render(MenuView *view)
{
    for (uint8_t i = 0; i < LCD_ROWS; i++)
    {
        format_line(view, i);

        // detectar cambios (texto o cursor)
        if (strcmp(render_line, last_lines[i]) != 0 || view->cursor != last_cursor)
        {
            lcd.setCursor(0, i);
            lcd.print(render_line);

            // guardar estado
            strcpy(last_lines[i], render_line);
        }
    }

    last_cursor = view->cursor;
}