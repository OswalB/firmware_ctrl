#pragma once

#include <Arduino.h>

typedef struct
{
    uint32_t lastTime;
    uint8_t  lastEvent;
    uint8_t  count;
    uint16_t windowMs;
} AccelTracker;


uint8_t accel_update2(AccelTracker *a, uint8_t event);
int accel_update(AccelTracker *a, uint8_t event,
                 int step_min, int step_max);
