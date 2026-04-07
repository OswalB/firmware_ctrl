#include <Arduino.h>
#include "encoder.h"
#include "core/event/event_queue.h"
#include "core/model/key_types.h"
#include <avr/io.h>
#include "modules/console/console.h"

// Pines Arduino Mega
#define ENC_A_PIN 2  // CLK
#define ENC_B_PIN 3  // DT
//#define ENC_SW_PIN 4 // botón

//#define LONG_PRESS_MS 800

//static uint32_t press_time = 0;
//static uint8_t long_sent = 0;

static uint8_t prev_state = 0;
static int8_t acc = 0;
//static uint8_t last_btn = 1;

static uint8_t read_encoder(void)
{
    uint8_t a = digitalRead(ENC_A_PIN);
    uint8_t b = digitalRead(ENC_B_PIN);
    return (a << 1) | b;
}

void encoder_init(void)
{
    pinMode(ENC_A_PIN, INPUT_PULLUP);
    pinMode(ENC_B_PIN, INPUT_PULLUP);
    //pinMode(ENC_SW_PIN, INPUT_PULLUP);

    prev_state = read_encoder();
}

void encoder_update(void)
{
    Event ev = {};
    ev.type = EVT_KEY_PRESS;

    bool send = false;

    // BOTÓN
    //uint8_t btn = digitalRead(ENC_SW_PIN);
    //uint32_t now = millis();

    // Detectar PRESIÓN
    /*if (btn == 0 && last_btn == 1)
    {
        press_time = now;
        long_sent = 0;
    }*/

    // Detectar MANTENIDO (long press)
    /*if (btn == 0 && !long_sent)
    {
        if ((now - press_time) > LONG_PRESS_MS)
        {
            ev.value = KEY_LONG;
            send = true;

            long_sent = 1; // evitar repetición
        }
    }*/

    // Detectar LIBERACIÓN (short press)
    /*if (btn == 1 && last_btn == 0)
    {
        if (!long_sent)
        {
            ev.value = KEY_OK;
            send = true;
        }
    }

    last_btn = btn;*/

    // ENCODER
    uint8_t state = read_encoder();

    if (state != prev_state)
    {

        // Decodificación Gray
        if (
            (prev_state == 0b00 && state == 0b01) ||
            (prev_state == 0b01 && state == 0b11) ||
            (prev_state == 0b11 && state == 0b10) ||
            (prev_state == 0b10 && state == 0b00))
        {
            acc++;
        }
        else
        {
            acc--;
        }

        // KY-040 → 4 pasos por "click"
        if (state == 0b00)
        {
            if (acc > 0)
            {
                //Console_Print(MSG_DBG, "DOWN");
                ev.value = KEY_DOWN;
                send = true;
            }
            else if (acc < 0)
            {
                //Console_Print(MSG_DBG, "UP");
                ev.value = KEY_UP;
                send = true;
            }

            acc = 0; // reset para siguiente click
        }

        prev_state = state;
    }

    // ---------------- ENVÍO EVENTO ----------------
    if (send)
    {
        eventQueue_push(ev);
    }
}
