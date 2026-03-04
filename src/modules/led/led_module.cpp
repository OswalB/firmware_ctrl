#include "led_module.h"
#include "modules/console/console.h"
#include "drivers/led_pwm/led_pwm.h"

// static LedPWM ledError(A0);
// static LedPWM ledRun(A1);

namespace led
{
    static LedPWM leds[(uint8_t)LedId::COUNT] =
        {
            LedPWM(A0), // ERROR
            LedPWM(A1)  // RUN
    };

    bool setDuty(uint8_t id, int32_t persent)
    {
        leds[id].set_duty(persent);
        return true;
    }

    bool setTime(uint8_t id, int32_t timeMs)
    {
        leds[id].set_time(timeMs);
        return true;
    }

    bool setState(uint8_t id, int32_t rawState)
    {
        if (id >= static_cast<uint8_t>(LedId::COUNT))
            return false;


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

    

    void led_init(void)
    {
        for (uint8_t i = 0; i < static_cast<uint8_t>(LedId::COUNT); i++)
        {
            leds[i].init();
        }

        // led_err_set(ERR_LED_OFF);
        // led_run_set(RUN_LED_OFF);
    }

    void led_update(void){
        for (uint8_t i = 0; i < static_cast<uint8_t>(LedId::COUNT); i++)
    {
        leds[i].update();
    }
    }
}//namespace led
