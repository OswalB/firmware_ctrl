#include "menu_table.h"

#define TOK_CMD(x)                \
    {                             \
        TOKEN_CMD, { .cmd = (x) } \
    }
#define TOK_DOMAIN(x)                   \
    {                                   \
        TOKEN_DOMAIN, { .domain = (x) } \
    }
#define TOK_PARAM(x)                  \
    {                                 \
        TOKEN_PARAM, { .param = (x) } \
    }
#define TOK_NUM(x)                      \
    {                                   \
        TOKEN_NUMBER, { .number = (x) } \
    }
#define NO_UNIT NULL


const char unit_ms[] PROGMEM = "ms";
const char unit_percent[] PROGMEM = "%";

const char label_motor[] PROGMEM = "Motor";
const char label_led[] PROGMEM = "Led State";
const char label_system[] PROGMEM = "System";
const char label_speed[] PROGMEM = "Speed";
const char label_stop[] PROGMEM = "Stop";
const char label_back[] PROGMEM = "< Back";
const char label_reset[] PROGMEM = "Reset";
const char label_led_state1[] PROGMEM = "Estado 1";
const char label_led_state2[] PROGMEM = "Estado 2";
const char label_led_state0[] PROGMEM = "Led OFF";
const char label_led_time[] PROGMEM = "Time";
const char label_led_duty[] PROGMEM = "Duty";

const MenuItem menu_table[] PROGMEM =
    {
        {0, 255, MENU_ITEM_SUBMENU, label_motor},
        {1, 255, MENU_ITEM_SUBMENU, label_led},
        {2, 255, MENU_ITEM_SUBMENU, label_system},

        {3, 0, MENU_ITEM_VALUE, label_speed},
        {4, 0, MENU_ITEM_COMMAND, label_stop},
        {5, 0, MENU_ITEM_BACK, label_back},

        {6, 2, MENU_ITEM_COMMAND, label_reset},
        {7, 2, MENU_ITEM_BACK, label_back},

        {8, 1, MENU_ITEM_COMMAND, label_led_state1, NO_UNIT, {TOK_CMD(EVT_SET), TOK_DOMAIN(DOMAIN_LED), TOK_NUM(0),TOK_PARAM(PARAM_STATE),TOK_NUM(1)}},
        {9, 1, MENU_ITEM_COMMAND, label_led_state2, NO_UNIT, {TOK_CMD(EVT_SET), TOK_DOMAIN(DOMAIN_LED), TOK_NUM(0),TOK_PARAM(PARAM_STATE),TOK_NUM(2)}},
        {10, 1, MENU_ITEM_COMMAND, label_led_state0, NO_UNIT, {TOK_CMD(EVT_SET), TOK_DOMAIN(DOMAIN_LED), TOK_NUM(0),TOK_PARAM(PARAM_STATE),TOK_NUM(0)}},
        {11, 1, MENU_ITEM_PARAM, label_led_time, unit_ms, {TOK_CMD(EVT_SET), TOK_DOMAIN(DOMAIN_LED), TOK_NUM(0),TOK_PARAM(PARAM_TIME),TOK_NUM(0)}},
        {13, 1, MENU_ITEM_PARAM, label_led_duty, unit_percent, {TOK_CMD(EVT_SET), TOK_DOMAIN(DOMAIN_LED), TOK_NUM(0),TOK_PARAM(PARAM_DUTY),TOK_NUM(0)}},
        {12, 1, MENU_ITEM_BACK, label_back},
};

const uint8_t menu_table_size = sizeof(menu_table) / sizeof(MenuItem);