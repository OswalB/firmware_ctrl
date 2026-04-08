#include <Arduino.h>
#include <RotaryEncoder.h>
#include "encoder.h"
#include "core/event/event_queue.h"
#include "core/model/key_types.h"
#include <avr/io.h>
#include "modules/console/console.h"

// Pines Arduino Mega
#define ENC_A_PIN 2 // CLK
#define ENC_B_PIN 3 // DT

static long lastPos = 0;

static RotaryEncoder encoder(
    ENC_A_PIN,
    ENC_B_PIN,
    RotaryEncoder::LatchMode::TWO03);

// static uint8_t prev_state = 0;
// static int8_t acc = 0;

static uint8_t read_encoder(void)
{
    uint8_t a = digitalRead(ENC_A_PIN);
    uint8_t b = digitalRead(ENC_B_PIN);
    return (a << 1) | b;
}

void encoder_init(void)
{
    encoder.setPosition(0);
}

void encoder_update(void)
{
    Event ev = {};
    ev.type = EVT_KEY_PRESS;

    bool send = false;

    encoder.tick();
    long pos = encoder.getPosition();

    if (pos != lastPos)
    {
        ev.value = pos > lastPos ? KEY_DOWN : KEY_UP;
        send = true; 
        lastPos = pos;
    }


    // ---------------- ENVÍO EVENTO ----------------
    if (send)
    {
        eventQueue_push(ev);
    }
}
