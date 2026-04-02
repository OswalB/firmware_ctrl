#include "buzzer.h"
#include <Arduino.h>

static uint8_t _pin;

static uint16_t _freq;
static uint16_t _duration;
static uint8_t  _repeat_total;
static uint8_t  _repeat_count;

static uint32_t _next_time = 0;
static uint8_t  _state = 0; // 0=idle, 1=on, 2=off_wait

#define BUZZER_GAP_MS 50

void buzzer_init(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
}

void buzzer_play(uint16_t freq, uint16_t duration, uint8_t repeat)
{
    _freq = freq;
    _duration = duration;
    _repeat_total = repeat;
    _repeat_count = 0;

    _state = 1;
    tone(_pin, _freq);
    _next_time = millis() + _duration;
}

void buzzer_tick(void)
{
    if (_state == 0)
        return;

    if (millis() < _next_time)
        return;

    switch (_state)
    {
        case 1: // estaba sonando → apagar
            noTone(_pin);
            _repeat_count++;

            if (_repeat_count >= _repeat_total)
            {
                _state = 0;
                return;
            }

            _state = 2;
            _next_time = millis() + BUZZER_GAP_MS;
            break;

        case 2: // pausa → volver a sonar
            tone(_pin, _freq);
            _state = 1;
            _next_time = millis() + _duration;
            break;
    }
}