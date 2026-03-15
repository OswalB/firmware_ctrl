#include <stdint.h>
#include "core/fsm/machine.h"
#include <string.h>
#include "core/event/event_queue.h"
#include "modules/console/console.h"
#include "core/domains/domain_led.h"
#include "core/domains/domain_custom.h"
#include "lib/utils/interpreter.h"
// #include "core/types/event_types.h"
// #include "modules/led/led.h"
// #include "drivers/led_pwm/led_pwm.h"

#include <stdio.h>
#include "lib/menu/menu.h"
#include "lib/menu/menu_table.h"

void menu_print(void);

static MachineState fsm_state = MS_IDLE;
static MachineState g_state;

void fsm_push(ResponseType type, const char *text);
static void machine_handleEvent(Event &evt);

#define FSM_QUEUE_SIZE 8

static Response responseQueue[FSM_QUEUE_SIZE];
static uint8_t queueHead = 0;
static uint8_t queueTail = 0;

void machine_init(void)
{
    g_state = MS_IDLE;
    // led_run_set(RUN_LED_IDLE);
    queueHead = 0;
    queueTail = 0;
    fsm_state = MS_IDLE;
}

void fsm_dispatchEvent(EventType ev)
{
    switch (fsm_state)
    {
    case MS_BUSY:
        break;

    case MS_IDLE:

        if (ev == EVT_START)
        {
            fsm_state = MS_RUNNING;
            fsm_push(RESP_INFO, "processing...");
        }
        else if (ev == EV_PARSE_UNKNOWN)
        {
            fsm_push(RESP_ERROR, "Unknown command7");
        }
        break;

    case MS_RUNNING:

        if (ev == EV_OPERATION_DONE)
        {
            fsm_state = MS_IDLE;
            fsm_push(RESP_OK, "");
        }
        break;

    case MS_ERROR:

        if (ev == EVT_RESET)
        {
            fsm_state = MS_IDLE;
            fsm_push(RESP_INFO, "reset done");
        }
        break;
    }
}

void fsm_push(ResponseType type, const char *text)
{
    uint8_t next = (queueHead + 1) % FSM_QUEUE_SIZE;

    if (next != queueTail) // evita overflow
    {
        responseQueue[queueHead].type = type;
        responseQueue[queueHead].text = text;
        queueHead = next;
    }
}

bool fsm_hasOutput(void)
{
    return (queueHead != queueTail);
}

Response fsm_getOutput(void)
{
    Response r = responseQueue[queueTail];
    queueTail = (queueTail + 1) % FSM_QUEUE_SIZE;
    return r;
}

MachineState fsm_getState(void)
{
    return fsm_state;
}

void machine_update(void)
{
    Event evt;

    if (eventQueue_pop(&evt))
    {
        machine_handleEvent(evt);
    }
}

void machine_handleEvent(Event &evt)
{
    //Console_Print(MSG_DBG, "Tecla ev=%s", enum_to_string(key_table_enum, key_table_count, evt.value));
    //Console_Print(MSG_LOG, "[key delete] is # %d", enum_from_string(key_table_enum, key_table_count, "key delete"));
    //  🔴 1. Eventos globales
    if (evt.type == EVT_ERROR)
    {
        g_state = MS_ERROR;
        return;
    }

    if (evt.type == EVT_KEY_PRESS)
    {
        evt.domain = DOMAIN_MENU;
        switch (evt.value)
        {
        case KEY_UP:
            menu_input(MENU_UP);
            break;
        case KEY_DOWN:
            menu_input(MENU_DOWN);
            break;
        case KEY_RIGHT:
            menu_input(MENU_ENTER);
            break;

        case KEY_LEFT:
            menu_input(MENU_BACK);
            break;
        default:

            break;
        }
    }

    // 🔵 2. Delegación por dominio
    switch (evt.domain)
    {
    case DOMAIN_LED:
        machine_led_handle(evt);
        Console_Print(MSG_DBG, "routing LED");
        break;

    case DOMAIN_MOTOR:
        // machine_motor_handle(evt);
        Console_Print(MSG_DBG, "routing MOTOR");
        break;

    case DOMAIN_CUSTOM:
        machine_custom_handle(evt);
        Console_Print(MSG_DBG, "routing CUSTOM");
        break;

    case DOMAIN_MENU:

        menu_print();
        break;
    default:
        Console_Print(MSG_ERR,
                      "Unknown domain %d\n",
                      evt.domain);
        break;
    }
}

//* * * * * TEST * * * * * *  BORRAR AL FINAL * * * *

void menu_print(void)
{
    MenuView view;
    char buf[32];
    menu_render(&view);

    Console_Print(MSG_NONE, "\n");

    for (uint8_t i = 0; i < view.count; i++)
    {
        if (i == view.cursor)
            Console_Print(MSG_NONE, "> ");
        else
            Console_Print(MSG_NONE, "  ");

        strcpy_P(buf, (PGM_P)view.lines[i]);
        Console_Print(MSG_NONE, buf);
        Console_Print(MSG_NONE, "\n\r");
    }

    /*if(state == MENU_STATE_EDIT)
{
    Console_Print(MSG_NONE,"Edit: %ld\n\r", edit_value);
}*/

    Console_Print(MSG_NONE, "\n");
}