#pragma once
#include <stdint.h>


namespace led
{
    enum class LedId : uint8_t
    {
        ERROR = 0,
        RUN,
        COUNT
    };

    enum class StatusLedState: uint8_t
    {
        LED_OFF = 0,
        LED_WARNING,
        LED_ERROR,
        LED_IDLE,
        LED_COUNT
    };

    class LedHelper
    {
    public:
        static bool isValid(uint8_t id)
        {
            return id < static_cast<uint8_t>(LedId::COUNT);
        }

        static LedId fromInt(uint8_t id)
        {
            return static_cast<LedId>(id);
        }
    };

    bool setDuty(uint8_t id, int32_t persent);
    bool setTime(uint8_t id, int32_t timeMs);
    bool setState(uint8_t id, int32_t state);
    bool start(uint8_t id);
    bool stop(uint8_t id);

    void led_init(void);
    void led_update(void);
}
