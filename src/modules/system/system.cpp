#include "system.h"
#include "platform/transport/transport.h"
#include "core/model/domain_capabilities.h"
#include "modules/console/console.h"

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