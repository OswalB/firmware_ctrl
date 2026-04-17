
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
    if (view->show_cursor)
    {
        render_line[0] = (i == view->cursor) ? '>' : ' ';
        // copiar texto (desde posición 1)
        strncpy(&render_line[1], view->lines[i], LCD_COLS - 1);
    }
    else
    {
        strncpy(&render_line[0], view->lines[i], LCD_COLS );
    }
}

void lcd_render(MenuView *view)
{
    int8_t prev = last_cursor;
    int8_t curr = view->cursor;

    for (uint8_t i = 0; i < LCD_ROWS; i++)
    {
        format_line(view, i);

        bool needs_update =
            (strcmp(render_line, last_lines[i]) != 0) ||
            (i == prev) ||
            (i == curr);

        if (needs_update)
        {
            lcd.setCursor(0, i);

            // 🔥 BORRADO FUERTE
            for (uint8_t j = 0; j < LCD_COLS; j++)
                lcd.print(' ');

            lcd.setCursor(0, i);
            lcd.print(render_line);

            strcpy(last_lines[i], render_line);
        }
    }

    last_cursor = curr;
}