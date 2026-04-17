#include <Arduino.h>
#include "system.h"
#include "platform/transport/transport.h"
#include "core/model/domain_capabilities.h"
#include "modules/console/console.h"

ui_mode_t ui_mode = UI_DASHBOARD;

static uint32_t last_activity = 0;

void system_init(void)
{
    if (!validate_domain_capabilities_table())
    {
        Console_Print(MSG_FORCE,"CONFIG ERROR ");
        //while (1); // detener sistema
    }else
    {
        Console_Print(MSG_FORCE,"CONFIG ok");
    }

    
    
}

void ui_notify_activity(void)
{
    last_activity = millis();
}

uint32_t getLast_activity()
{
    return last_activity;
}