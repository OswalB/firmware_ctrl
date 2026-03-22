#include "accel_input.h"


int accel_update3(AccelTracker *a, uint8_t event,
                 int step_min, int step_max)
{
    uint32_t now = millis();
    uint32_t dt  = now - a->lastTime;

    // reset por cambio de evento o timeout
    if (event != a->lastEvent || dt > a->windowMs)
    {
        a->lastTime  = now;
        a->lastEvent = event;
        return step_min;
    }

    a->lastTime  = now;
    a->lastEvent = event;

    // 🧠 Zonas de velocidad (ajustables)
    // dt en ms

    if (dt < 30)
    {
        return step_max;                 // ultra rápido
    }
    else if (dt < 80)
    {
        return step_min + (step_max - step_min) * 3 / 4;
    }
    else if (dt < 150)
    {
        return step_min + (step_max - step_min) / 2;
    }
    else if (dt < 300)
    {
        return step_min + (step_max - step_min) / 4;
    }
    else
    {
        return step_min;                 // lento
    }
}

int accel_update(AccelTracker *a, uint8_t event,
                 int step_min, int step_max)
{
    uint32_t now = millis();
    uint32_t dt  = now - a->lastTime;

    if (event != a->lastEvent || dt > a->windowMs)
    {
        a->lastTime  = now;
        a->lastEvent = event;
        return step_min;
    }

    a->lastTime  = now;
    a->lastEvent = event;

    // clamp dt
    if (dt < 20)  dt = 20;
    if (dt > 300) dt = 300;

    // invertir dt: menor dt → mayor factor
    uint32_t inv = 300 - dt;  // rango 0..280

    // normalizar a 0..255
    uint32_t factor = (inv * 255) / 280;

    // curva cuadrática entera (sin float)
    factor = (factor * factor) / 255;

    int step = step_min + ((step_max - step_min) * factor) / 255;

    return step;
}