#include "menu.h"
#include "menu_table.h"
#include <string.h>
#include "modules/console/console.h"

static MenuState state;

static uint8_t cursor;
static uint8_t scroll;
static uint8_t parent;

static uint8_t parent_stack[MENU_MAX_DEPTH];
static uint8_t level;

static uint8_t visible_items[MENU_MAX_VISIBLE];

static uint8_t child_count(uint8_t parent_id)
{
    uint8_t count = 0;

    for(uint8_t i=0;i<menu_table_size;i++)
    {
        MenuItem item;
        memcpy_P(&item, &menu_table[i], sizeof(MenuItem));

        if(item.parent == parent_id)
            count++;
    }

    return count;
}

static uint8_t child_at(uint8_t parent_id, uint8_t index)
{
    uint8_t count = 0;

    for(uint8_t i=0;i<menu_table_size;i++)
    {
        MenuItem item;
        memcpy_P(&item, &menu_table[i], sizeof(MenuItem));

        if(item.parent == parent_id)
        {
            if(count == index)
                return i;

            count++;
        }
    }

    return 0;
}

void menu_init(void)
{
    state = MENU_NAV;

    cursor = 0;
    scroll = 0;

    parent = 255;

    level = 0;
}

void menu_input(MenuInputEvent ev)
{
    uint8_t count = child_count(parent);

    switch(ev)
    {
        case MENU_UP:

            if(cursor > 0)
                cursor--;

            if(cursor < scroll)
                scroll--;

        break;

        case MENU_DOWN:

            if(cursor < count-1)
                cursor++;

            if(cursor >= scroll + MENU_MAX_VISIBLE)
                scroll++;

        break;

        case MENU_ENTER:
        {
            uint8_t index = child_at(parent, cursor);

            MenuItem item;
            memcpy_P(&item, &menu_table[index], sizeof(MenuItem));

            if(item.type == MENU_ITEM_SUBMENU)
            {
                parent_stack[level++] = parent;
                parent = item.id;

                cursor = 0;
                scroll = 0;
            }

            else if(item.type == MENU_ITEM_BACK)
            {
                if(level > 0)
                {
                    parent = parent_stack[--level];
                    cursor = 0;
                    scroll = 0;
                }
            }

        }
        break;

        case MENU_BACK:

            if(level > 0)
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

    for(uint8_t i=0;i<MENU_MAX_VISIBLE;i++)
    {
        uint8_t idx = scroll + i;

        if(idx >= count)
            break;

        uint8_t table_index = child_at(parent, idx);

        MenuItem item;
        memcpy_P(&item, &menu_table[table_index], sizeof(MenuItem));

        view->lines[i] = item.label;

        view->count++;
    }
}