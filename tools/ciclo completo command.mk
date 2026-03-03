# System Overview

🎯 ESCENARIO

Queremos que:

led 1 → LedId::RUN

state 0 → LED_ERROR

El driver ya tiene start_led() y set_duty() implementados.

🔄 SECUENCIA COMPLETA
1️⃣ Consola → Parser

Entrada:

set led 1 state 0

El parser construye:

Event evt;

evt.type   = EVT_SET;
evt.domain = DOMAIN_LED;
evt.id     = 1;          // RUN
evt.param  = PARAM_STATE;
evt.value  = 0;          // ERROR

Luego:

eventQueue_push(evt);
2️⃣ FSM
void machine_update(void)
{
    Event evt;

    if (eventQueue_pop(&evt))
    {
        machine_handleEvent(evt);
    }
}
3️⃣ Enrutamiento por dominio
void machine_handleEvent(const Event &evt)
{
    switch (evt.domain)
    {
        case DOMAIN_LED:
            machine_led_handle(evt);
            break;

        case DOMAIN_MOTOR:
            machine_motor_handle(evt);
            break;
    }
}
4️⃣ Domain LED Handler

Aquí decides según el param:

void machine_led_handle(const Event &evt)
{
    switch (evt.param)
    {
        case PARAM_STATE:
            led_setState(evt);   // <-- aquí empieza el módulo LED
            break;

        case PARAM_DUTY:
            led_setDuty(evt);
            break;
    }
}

machine_led_handle(evt)
    ↓
led_setState(evt)
    ↓
led::setState(id, state)
    ↓
leds[id].start_led()

5️⃣ Función del módulo LED
Ahora estamos dentro del módulo led.cpp.

Tú dijiste que tienes:

bool setState(uint8_t id, int32_t state);

Entonces led_setState() debe resolver el ID y llamar eso.

Ejemplo correcto:

void led_setState(const Event &evt)
{
    if (evt.id >= static_cast<uint8_t>(led::LedId::COUNT))
        return;

    led::setState(evt.id, evt.value);
}


6️⃣ Implementación real en el módulo LED

Aquí ocurre la magia real:

bool setState(uint8_t id, int32_t rawState)
    {
        if (id >= static_cast<uint8_t>(LedId::COUNT))
            return false;

        LedId ledId = static_cast<LedId>(id);

        StatusLedState state =
        static_cast<StatusLedState>(rawState);

        switch (state)
        {
        case StatusLedState::LED_OFF:
            leds[id].start_led(0, 0);
            break;

        case StatusLedState::LED_WARNING:
            leds[id].start_led(1000, 50);
            break;

        case StatusLedState::LED_ERROR:
            leds[id].start_led(200, 25);
            break;

        default:
            return false;
        }

        return true;
    }

