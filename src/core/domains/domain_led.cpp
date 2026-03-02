#include <stddef.h>

#include "domain_led.h"
#include "modules/console/console.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

static void led_setTime(const Event& evt);
static void led_setState(const Event& evt);
static void led_getTime(const Event& evt);

static const LedCommandEntry ledCmdTable[] =
{
    {EVT_SET, PARAM_TIME,  led_setTime},
    {EVT_SET, PARAM_STATE, led_setState},
    {EVT_GET, PARAM_TIME,  led_getTime},
};

void machine_led_handle(const Event& evt)
{
    for (size_t i = 0; i < ARRAY_SIZE(ledCmdTable); i++)
    {
        if (ledCmdTable[i].type  == evt.type &&
            ledCmdTable[i].param == evt.param)
        {
            ledCmdTable[i].handler(evt);
            return;
        }
    }

    Console_Print(MSG_ERR,
        "LED: Command not supported (type=%d param=%d)\n",
        evt.type,
        evt.param);
}

//----------------------------------
//--------COMMAND FUNCTIONS---------
//----------------------------------

static void led_setTime(const Event& evt)
{
    Console_Print(MSG_LOG,
        "LED %d -> set TIME = %ld\n",
        evt.id,
        evt.value);
}

static void led_setState(const Event& evt)
{
    Console_Print(MSG_LOG,
        "LED %d -> set STATE = %ld\n",
        evt.id,
        evt.value);
}

static void led_getTime(const Event& evt)
{
    Console_Print(MSG_LOG,
        "LED %d -> get TIME\n",
        evt.id);
}