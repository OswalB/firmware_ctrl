#include "menu_table.h"

const char label_motor[] PROGMEM = "Motor";
const char label_sensor[] PROGMEM = "Sensor";
const char label_system[] PROGMEM = "System";
const char label_speed[] PROGMEM = "Speed";
const char label_stop[] PROGMEM = "Stop";
const char label_back[] PROGMEM = "< Back";
const char label_reset[] PROGMEM = "Reset";

const MenuItem menu_table[] PROGMEM =
{
    {0, 255, MENU_ITEM_SUBMENU, label_motor},
    {1, 255, MENU_ITEM_SUBMENU, label_sensor},
    {2, 255, MENU_ITEM_SUBMENU, label_system},

    {3, 0, MENU_ITEM_VALUE, label_speed},
    {4, 0, MENU_ITEM_COMMAND, label_stop},
    {5, 0, MENU_ITEM_BACK, label_back},

    {6, 2, MENU_ITEM_COMMAND, label_reset},
    {7, 2, MENU_ITEM_BACK, label_back}
};

const uint8_t menu_table_size = sizeof(menu_table) / sizeof(MenuItem);