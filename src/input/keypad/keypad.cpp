#include <Arduino.h>
#include "keypad.h"
#include "core/event/event_queue.h"
#include "core/model/key_types.h"
#include "modules/console/console.h"

#define LONG_PRESS_MS 800
#define SW_OK 4

static uint32_t press_time = 0;
static uint8_t long_sent = 0;
static uint8_t last_btn = 1;

void keypad_init()
{
    pinMode(SW_OK, INPUT_PULLUP);
}

void keypad_tick()
{
    Event ev = {};
    ev.type = EVT_KEY_PRESS;

    bool send = false;
    uint8_t btn = digitalRead(SW_OK);
    uint32_t now = millis();

    if (btn == 0 && last_btn == 1)
    {
        Console_Print(MSG_DBG,"btn down");
        press_time = now;
        long_sent = 0;
    }

    // Detectar MANTENIDO (long press)
    if (btn == 0 && !long_sent)
    {
        if ((now - press_time) > LONG_PRESS_MS)
        {
            Console_Print(MSG_DBG,"btn loong press");
            ev.value = KEY_LONG;
            send = true;

            long_sent = 1; // evitar repetición
        }
    }

    // Detectar LIBERACIÓN (short press)
    if (btn == 1 && last_btn == 0)
    {
        if (!long_sent)
        {
            Console_Print(MSG_DBG,"btn soltar");
            ev.value = KEY_OK;
            send = true;
        }
    }

    last_btn = btn;
    
    if (send)
    {
        eventQueue_push(ev);
    }
}