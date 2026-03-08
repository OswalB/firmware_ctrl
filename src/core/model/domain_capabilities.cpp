#include <stddef.h>

#include "domain_capabilities.h"
#include "core/model/event_types.h"
#include "modules/console/console.h"
#include "core/model/domain_types.h"
#include "core/model/event_types.h"

#define PARAM_UNUSED {0, 0, false}

static const DomainCapabilities domain_table[] =
    {
        // DOMMAIN LED ***
        {.domain = DOMAIN_LED,
         .supported_params_mask =
             (1u << PARAM_STATE) |
             (1u << PARAM_DUTY) |
             (1u << PARAM_TIME),
         .supported_cmds_mask =
             (1u << EVT_START) |
             (1u << EVT_STOP) |
             (1u << EVT_SET) |
             (1u << EVT_GET) |
             (1u << EVT_SAVE),
         .param_ranges =
             {
                 [PARAM_UNKNOW] = PARAM_UNUSED,
                 [PARAM_STATE] = {.min = 0, .max = 2, .has_range = true},
                 [PARAM_SPEED] = PARAM_UNUSED,
                 [PARAM_DUTY] = {.min = 0, .max = 100, .has_range = true},
                 [PARAM_TIME] = {.min = 0, .max = 60000, .has_range = true}},

         .id_range = {.min = 0, .max = 2, .has_range = true}},
        // DOMMAIN MOTOR ***
        {.domain = DOMAIN_MOTOR,
         .supported_params_mask =
             (1u << PARAM_SPEED),
         .supported_cmds_mask =
             (1u << EVT_START) |
             (1u << EVT_STOP) |
             (1u << EVT_SET) |
             (1u << EVT_GET),
         .param_ranges =
             {
                 [PARAM_UNKNOW] = PARAM_UNUSED,
                 [PARAM_STATE] = PARAM_UNUSED,
                 [PARAM_SPEED] = {.min = 0, .max = 100, .has_range = true},
                 [PARAM_DUTY] = PARAM_UNUSED,
                 [PARAM_TIME] = PARAM_UNUSED},
         .id_range = {.min = 0, .max = 3, .has_range = true}},
        // DOMMAIN SENSOR ***
        {.domain = DOMAIN_SENSOR,
         .supported_params_mask =
             (1u << PARAM_STATE),
         .supported_cmds_mask = (1u << EVT_GET),
         .param_ranges = {
             [PARAM_UNKNOW] = PARAM_UNUSED,
             [PARAM_STATE] = {.min = 0, .max = 0, .has_range = true}, // PARAM_STATE
             {0, 0, false},
             [PARAM_DUTY] = PARAM_UNUSED,
             [PARAM_TIME] = PARAM_UNUSED},
         {0, 10, true}},
         {
            .domain = DOMAIN_CUSTOM,
            .supported_params_mask =0,
            .supported_cmds_mask =
            (1u << EVT_SAVE) | 
            (1u << EVT_GET),
            .param_ranges={0,0,false},
            .id_range = {.min = 0, .max = 5, .has_range = true}
             
            
         },
};

const DomainCapabilities *
get_domain_capabilities(DomainType domain)
{
    for (size_t i = 0;
         i < sizeof(domain_table) / sizeof(domain_table[0]);
         i++)
    {
        if (domain_table[i].domain == domain)
            return &domain_table[i];
    }

    return NULL;
}

bool validate_domain_capabilities_table(void)
{
    Console_Print(MSG_LOG, "validando capabilities");
    size_t table_size =
        sizeof(domain_table) / sizeof(domain_table[0]);

    if (table_size != (DOMAIN_COUNT - 1))
    {
        Console_Print(MSG_LOG, "Domain table size mismatch");
        return false;
    }

    for (size_t i = 0; i < table_size; i++)
    {
        const DomainCapabilities *caps = &domain_table[i];

        if (caps->domain >= DOMAIN_COUNT)
        {
            Console_Print(MSG_LOG, "Domain out of range");
            return false;
        }

        if (EVT_COUNT >= 16)
        {
            Console_Print(MSG_LOG, "EVT_COUNT too large");
            return false;
        }

        if (caps->supported_cmds_mask &
            ~((1u << EVT_COUNT) - 1))
        {
            Console_Print(MSG_LOG, "Invalid event command mask");
            return false;
        }

        if (caps->supported_params_mask &
            ~((1u << PARAM_COUNT) - 1))
        {
            Console_Print(MSG_LOG, "Invalid param command mask");

            return false;
        }

        // Validación de rango de instancias del dominio
        if (!caps->id_range.has_range)
        {
            Console_Print(MSG_LOG, "Domain without ID range");
            return false;
        }
        if (caps->id_range.has_range)
        {
            if (caps->id_range.min > caps->id_range.max)
            {
                Console_Print(MSG_LOG, "Invalid domain ID range");
                return false;
            }
        }

        for (uint8_t p = 0; p < PARAM_COUNT; p++)
        {
            bool param_supported =
                (caps->supported_params_mask & (1u << p)) != 0;

            ParamRange range = caps->param_ranges[p];

            if (param_supported)
            {
                if (range.has_range)
                {
                    if (range.min > range.max)
                    {
                        Console_Print(MSG_LOG, "Invalid range");
                        return false;
                    }
                }
            }
            else
            {
                if (range.has_range)
                {
                    Console_Print(MSG_LOG, "Range defined but param not supported");
                    return false;
                }
            }
        }
    }
    Console_Print(MSG_LOG, "Ok. Capabilities");
    return true;
}