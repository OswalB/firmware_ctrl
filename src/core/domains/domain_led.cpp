#include <stddef.h>

#include "domain_led.h"
#include "modules/console/console.h"
#include "modules/led/led_module.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

static void led_getTime(const Event &evt);
static void led_saveTime(const Event &evt);
static void led_setDuty(const Event &evt);
static void led_setState(const Event &evt);
static void led_setTime(const Event &evt);
static void led_start(const Event &evt);
static void led_stop(const Event &evt);



static const LedCommandEntry ledCmdTable[] =
    {
        {EVT_SAVE,PARAM_TIME, led_saveTime},
        {EVT_SET, PARAM_DUTY, led_setDuty},
        {EVT_SET, PARAM_TIME, led_setTime},
        {EVT_SET, PARAM_STATE, led_setState},
        {EVT_GET, PARAM_TIME, led_getTime},
        {EVT_START, PARAM_UNKNOW, led_start},
        {EVT_STOP, PARAM_UNKNOW, led_stop},
};

void machine_led_handle(const Event &evt)
{
    for (size_t i = 0; i < ARRAY_SIZE(ledCmdTable); i++)
    {
        if (ledCmdTable[i].type == evt.type &&
            ledCmdTable[i].param == evt.param)
        {
            ledCmdTable[i].handler(evt);
            return;
        }
    }

    Console_Print(MSG_ERR,
                  "LED: Command not supported in module(type=%d param=%d)\n",
                  evt.type,
                  evt.param);
}

//----------------------------------
//--------COMMAND FUNCTIONS---------
//----------------------------------

static void led_setDuty(const Event &evt)
{
    if (!led::setDuty(evt.id, evt.value))
    {
        Console_Print(MSG_ERR, "LED setDuty failed\n");
        return;
    }
    led::setDuty(evt.id, evt.value);
}

static void led_saveTime(const Event &evt)
{
    if (!led::saveTime(evt.id, evt.value))
    {
        Console_Print(MSG_ERR, "LED saveTime failed\n");
        return;
    }
    led::setTime(evt.id, evt.value);
}

static void led_setTime(const Event &evt)
{
    if (!led::setTime(evt.id, evt.value))
    {
        Console_Print(MSG_ERR, "LED setTime failed\n");
        return;
    }
    led::setTime(evt.id, evt.value);
}

static void led_setState(const Event &evt)
{

    if (evt.id >= static_cast<uint8_t>(led::LedId::COUNT))
        return;

    led::setState(evt.id, evt.value);
}

static void led_start(const Event &evt)
{

    if (evt.id >= static_cast<uint8_t>(led::LedId::COUNT))
        return;

    led::start(evt.id);
}

static void led_stop(const Event &evt)
{

    if (evt.id >= static_cast<uint8_t>(led::LedId::COUNT))
        return;

    led::stop(evt.id);
}

static void led_getTime(const Event &evt)
{
    Console_Print(MSG_LOG,
                  "No implementado: LED %d -> get TIME\n",
                  evt.id);
}