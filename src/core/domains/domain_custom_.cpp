#include <stddef.h>

#include "domain_custom.h"
#include "modules/console/console.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

static void custom_save(const Event &evt);

static const CustomCommandEntry customCmdTable[] =
    {
        {EVT_SAVE, PARAM_UNKNOW, custom_save}};

void machine_custom_handle(const Event &evt)
{
    for (size_t i = 0; i < ARRAY_SIZE(customCmdTable); i++)
    {
        if (customCmdTable[i].type == evt.type &&
            customCmdTable[i].param == evt.param)
        {
            customCmdTable[i].handler(evt);
            return;
        }
    }

    Console_Print(MSG_ERR,
                  "CUSTOM: Command not supported in module(type=%d param=%d)\n",
                  evt.type,
                  evt.param);
}

//----------------------------------
//--------COMMAND FUNCTIONS---------
//----------------------------------

void custom_save(const Event &evt)
{
    Console_Print(MSG_DBG, "aqui va la grabadora eeprom");
}
