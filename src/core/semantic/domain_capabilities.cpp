#include <stddef.h>

#include "domain_capabilities.h"
#include "core/types/event_types.h"
#include "system/console/console.h"
#include "core/types/domain_types.h"
#include "core/types/event_types.h"

static const DomainCapabilities domain_table[] =
    {
        {DOMAIN_LED,
         (1u << PARAM_STATE),
         (1u << EVT_SET) | (1u << EVT_GET),
         {
             {0, 0, false}, // PARAM_NONE
             {0, 1, true},  // PARAM_STATE
             {0, 0, false}  // PARAM_SPEED
         }},
        {DOMAIN_MOTOR,
         (1u << PARAM_SPEED),
         (1u << EVT_SET) | (1u << EVT_GET),
         {
             {0, 0, false}, // PARAM_NONE
             {0, 0, false}, // PARAM_STATE
             {0, 100, true} // PARAM_SPEED
         }},
        {DOMAIN_SENSOR,
         0,
         (1u << EVT_GET),
         {
             {0, 0, false}, // PARAM_NONE
             {0, 0, false}, // PARAM_STATE
             {0, 0, false}  // PARAM_SPEED
         }}};

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
            Console_Print(MSG_LOG, "Invalid command mask");
            return false;
        }

        if (caps->supported_params_mask &
            ~((1u << PARAM_COUNT) - 1))
        {
            Console_Print(MSG_LOG, "Invalid command mask");

            return false;
        }

        for (uint8_t p = 0; p < PARAM_COUNT; p++)
        {
            bool param_supported =
                (caps->supported_params_mask & (1u << p)) != 0;

            ParamRange range = caps->param_ranges[p];

            // bool range_defined =
            //!(range.min == 0 && range.max == 0);

            // bool range_defined = range.has_range;

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