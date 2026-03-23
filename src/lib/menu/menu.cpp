#include "menu.h"
#include "menu_table.h"
#include <string.h>
#include <stdio.h>
#include "modules/console/console.h"
#include "modules/led/led_module.h"
#include "core/event/event_queue.h"
#include "core/model/key_types.h"
#include "core/model/domain_capabilities.h"
#include "input/command/parser.h"
#include "lib/interface_hmi/accel_input.h"

//*********** FORWARDS ************ */
static DomainType menu_item_get_domain(const MenuItem *item);
static ParamType menu_item_get_param(const MenuItem *item);
static uint8_t menu_item_get_instance(const MenuItem *item);
void menu_print(void);
//****

AccelTracker acc = {0, 0, 0, 500};

static MenuState state;

static int32_t edit_value;
static uint8_t edit_item_id;
int32_t led_time = 500;

static uint8_t cursor;
static uint8_t scroll;
static uint8_t parent;

static uint8_t parent_stack[MENU_MAX_DEPTH];
static uint8_t level;

static int32_t menu_get_current_value(const MenuItem *item);
static void menu_commit_edit();
int32_t menu_get_display_value(uint8_t item_id, const MenuItem *item);

static uint8_t child_count(uint8_t parent_id)
{
    uint8_t count = 0;

    for (uint8_t i = 0; i < menu_table_size; i++)
    {
        MenuItem item;
        memcpy_P(&item, &menu_table[i], sizeof(MenuItem));

        if (item.parent == parent_id)
            count++;
    }

    return count;
}

static uint8_t child_at(uint8_t parent_id, uint8_t index)
{
    uint8_t count = 0;

    for (uint8_t i = 0; i < menu_table_size; i++)
    {
        MenuItem item;
        memcpy_P(&item, &menu_table[i], sizeof(MenuItem));

        if (item.parent == parent_id)
        {
            if (count == index)
                return i;

            count++;
        }
    }

    return 0;
}

void menu_init(void)
{
    state = MENU_STATE_NAV;

    cursor = 0;
    scroll = 0;

    parent = 255;

    level = 0;
}

void menu_update(void)
{
    if (menu_dirty)
    {
        menu_print();
        menu_dirty = false;
    }
}

void menu_input(MenuInputEvent ev)
{
    menu_dirty = true;
    uint8_t count = child_count(parent);

    uint8_t index = child_at(parent, cursor);
    MenuItem item;
    memcpy_P(&item, &menu_table[index], sizeof(MenuItem));

    if (state == MENU_STATE_NAV && ev == MENU_ENTER)
    {

        if (item.type == MENU_ITEM_PARAM)
        {
            edit_item_id = index;

            edit_value = menu_get_current_value(&item);

            state = MENU_STATE_EDIT;

            Console_Print(MSG_LOG, "EDIT %ld", edit_value);
            return;
        }
    }

    if (state == MENU_STATE_EDIT)
    {
        DomainType domain = menu_item_get_domain(&item);
        ParamType param = menu_item_get_param(&item);

        const DomainCapabilities *caps = get_domain_caps(domain);
        ParamRange range = caps->param_ranges[param];

        int step = accel_update(&acc, ev, 1, range.max_step);

        switch (ev)
        {
        case MENU_UP:
            edit_value += step;
            if (range.has_range && edit_value > range.max)
                edit_value = range.max;
            break;

        case MENU_DOWN:
            edit_value -= step;
            if (range.has_range && edit_value < range.min)
                edit_value = range.min;
            break;
        case MENU_ENTER:
            menu_commit_edit();
            state = MENU_STATE_NAV;
            break;

        case MENU_BACK:
            state = MENU_STATE_NAV;
            Console_Print(MSG_LOG, "EDIT CANCEL");
            break;
        }
        Console_Print(MSG_LOG, "VAL=%ld", edit_value);
        return;
    }

    switch (ev)
    {
    case MENU_UP:

        if (cursor > 0)
            cursor--;

        if (cursor < scroll)
            scroll--;

        break;

    case MENU_DOWN:

        if (count > 0 && cursor < count - 1)
            cursor++;

        if (cursor >= scroll + MENU_MAX_VISIBLE)
            scroll++;

        break;

    case MENU_ENTER:
    {
        uint8_t index = child_at(parent, cursor);

        MenuItem item;
        memcpy_P(&item, &menu_table[index], sizeof(MenuItem));

        if (item.type == MENU_ITEM_SUBMENU)
        {
            parent_stack[level++] = parent;
            parent = item.id;

            cursor = 0;
            scroll = 0;
        }

        else if (item.type == MENU_ITEM_BACK)
        {
            if (level > 0)
            {
                parent = parent_stack[--level];
                cursor = 0;
                scroll = 0;
            }
        }

        else if (item.type == MENU_ITEM_COMMAND)
        {
            parser_process_tokens(item.tokens, 5);
        }
    }
    break;

    case MENU_BACK:

        if (level > 0)
        {
            parent = parent_stack[--level];
            cursor = 0;
            scroll = 0;
        }

        break;

    default:
        break;
    }
}

void menu_render(MenuView *view)
{
    uint8_t count = child_count(parent);

    view->count = 0;
    view->cursor = cursor - scroll;

    for (uint8_t i = 0; i < MENU_MAX_VISIBLE; i++)
    {
        uint8_t idx = scroll + i;

        if (idx >= count)
            break;

        uint8_t table_index = child_at(parent, idx);

        MenuItem item;
        memcpy_P(&item, &menu_table[table_index], sizeof(MenuItem));

        char label[20];

        strcpy_P(label, (PGM_P)item.label);

        if (item.type == MENU_ITEM_PARAM)
        {
            int32_t val = menu_get_display_value(table_index, &item);

            char unit[8] = "";

            if (item.unit != NULL)
            {
                strcpy_P(unit, (PGM_P)item.unit);
                snprintf(view->lines[i], MENU_LINE_LEN, "%s = %ld %s", label, val, unit);
            }
            else
            {
                snprintf(view->lines[i], MENU_LINE_LEN, "%s = %ld", label, val);
            }
        }
        else
        {
            snprintf(view->lines[i], MENU_LINE_LEN, "%s", label);
        }

        view->count++;
    }
}

static void menu_commit_edit()
{
    MenuItem item;

    memcpy_P(&item, &menu_table[edit_item_id], sizeof(MenuItem));

    Token tokens[5];

    memcpy(tokens, item.tokens, sizeof(tokens));

    tokens[4].number = edit_value;

    parser_process_tokens(tokens, 5);
    menu_dirty = true;
}

MenuState menu_get_state()
{
    return state;
}

int32_t menu_get_display_value(uint8_t item_id, const MenuItem *item)
{
    if (state == MENU_STATE_EDIT && item_id == edit_item_id)
    {
        Console_Print(MSG_DBG, "en edicion");
        return edit_value;
    }
    Console_Print(MSG_DBG, "en edicion NONE");

    return menu_get_current_value(item);
}

//*********** HEPPERS ***********

static DomainType menu_item_get_domain(const MenuItem *item)
{
    return item->tokens[1].domain;
}

static ParamType menu_item_get_param(const MenuItem *item)
{
    return item->tokens[3].param;
}

static uint8_t menu_item_get_instance(const MenuItem *item)
{
    return item->tokens[2].number;
}

// * * * * *  TABLA FUNCIONES GET DATA PARAM * * * * * *
static int32_t led_get_time(uint8_t id)
{

    return led::getTime(id);
}

static int32_t led_get_duty(uint8_t id)
{
    return led::getDuty(id);
}

static int32_t led_get_time(uint8_t id);
static int32_t led_get_duty(uint8_t id);

static const DomainAccess domain_access[] =
    {
        // DOMAIN_UNKNOW = 0
        {
            {NULL, NULL, NULL, NULL, NULL}},
        // DOMAIN_MOTOR = 1
        {
            {NULL, NULL, NULL, NULL, NULL}},
        // DOMAIN_LED = 2S
        {
            {
                NULL,         // PARAM_UNKNOW    Orden es indispensable
                NULL,         // PARAM_STATE
                NULL,         // PARAM_SPEED
                led_get_duty, // PARAM_DUTY
                led_get_time  // PARAM_TIME
            }},

};

static int32_t menu_get_current_value(const MenuItem *item)
{
    DomainType domain = menu_item_get_domain(item);
    uint8_t id = menu_item_get_instance(item);
    ParamType param = menu_item_get_param(item); // item->tokens[3].param;

    Console_Print(MSG_DBG, "id test %d %d %d", domain, id, param);
    const DomainAccess *acc = &domain_access[domain];

    if (acc->getters[param])
    {
        return acc->getters[param](id);
    }

    return 0;
}



//* * * * * TEST * * * * * *  BORRAR AL FINAL * * * *

void menu_print(void)
{
    MenuView view;
    // char buf[32];

    menu_render(&view);

    Console_Print(MSG_LOG, "=====menu======");

    for (uint8_t i = 0; i < view.count; i++)
    {
        if (i == view.cursor)
            Console_Print(MSG_LOG, "> %s", view.lines[i]);
        else
            Console_Print(MSG_LOG, "  %s", view.lines[i]);
    }

    if (menu_get_state() == MENU_STATE_EDIT)
    {
        // Console_Print(MSG_NONE,"Edit: %ld\n\r", edit_value);
    }

    // Console_Print(MSG_NONE, "\n");
}