#pragma once

#include <stdint.h>

void buzzer_init(uint8_t pin);

// freq: Hz
// duration: ms (tiempo encendido)
// repeat: veces que se repite
void buzzer_play(uint16_t freq, uint16_t duration, uint8_t repeat);

void buzzer_tick(void);
