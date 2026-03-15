#include "menu.h"
#include "menu_table.h"
#include <string.h>
#include "modules/console/console.h"
#include "core/event/event_queue.h"
#include "core/model/key_types.h"
#include "input/command/parser.h"

static MenuState state;

static int32_t edit_value;
static uint8_t edit_item_id;
int32_t led_time = 50;

static uint8_t cursor;
static uint8_t scroll;
static uint8_t parent;

static uint8_t parent_stack[MENU_MAX_DEPTH];
static uint8_t level;

static uint8_t visible_items[MENU_MAX_VISIBLE];

static int32_t menu_get_current_value(const MenuItem *item);
static void menu_commit_edit();

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

void menu_input(MenuInputEvent ev)
{
    uint8_t count = child_count(parent);

    if (state == MENU_STATE_NAV && ev == MENU_ENTER)
    {
        uint8_t index = child_at(parent, cursor);
        MenuItem item;
        memcpy_P(&item, &menu_table[index], sizeof(MenuItem));

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
        switch (ev)
        {
        case MENU_UP:
            edit_value++;
            break;

        case MENU_DOWN:
            edit_value--;
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

    if (state == MENU_STATE_NAV)
    {

        switch (ev)
        {
        case MENU_UP:

            if (cursor > 0)
                cursor--;

            if (cursor < scroll)
                scroll--;

            break;

        case MENU_DOWN:

            if (cursor < count - 1)
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
                MenuItem item;
                memcpy_P(&item, &menu_table[index], sizeof(MenuItem));

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

        view->lines[i] = item.label;

        view->count++;
    }
}

static int32_t menu_get_current_value(const MenuItem *item)
{
    if (item->tokens[3].param == PARAM_TIME)
        return led_time;

    return 0;
}

static void menu_commit_edit()
{
    MenuItem item;

    // menu_get_item(edit_item_id, &item);
    memcpy_P(&item, &menu_table[edit_item_id], sizeof(MenuItem));

    Token tokens[5];

    memcpy(tokens, item.tokens, sizeof(tokens));

    tokens[4].number = edit_value;

    parser_process_tokens(tokens, 5);
}
