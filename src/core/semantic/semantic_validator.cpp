#include "semantic_validator.h"
#include "core/types/event_types.h"
#include "domain_capabilities.h"
#include "core/types/domain_types.h"
#include "core/types/param_types.h"
#include "core/types/err_types.h"

ErrorType validate_semantics(Event *ev)
{
    if (!ev)
        return ERR_EVENT_UNKNOW;

    const DomainCapabilities *caps =
        get_domain_capabilities(ev->domain);

    if (!caps)
        return ERR_DOMANIN;

    // 1️⃣ Validar comando permitido
    if (!(caps->supported_cmds_mask & (1u << ev->type)))
        return ERR_COM;

    // 2️⃣ Validar parámetro (si existe)
    if (ev->param < PARAM_COUNT)
    {
        if (ev->param != 0) // 0 significa "no param" en tu diseño actual
        {
            if (!(caps->supported_params_mask & (1u << ev->param)))
                return ERR_PARAM;
        }
    }

    //validar rangos
    if (ev->param != PARAM_UNKNOW)
    {
        if (!(caps->supported_params_mask & (1u << ev->param)))
            return ERR_VALUE_PARAM;

        int32_t value = ev->value;

        ParamRange range = caps->param_ranges[ev->param];

        if (value < range.min || value > range.max)
            return ERR_RANGE_PARAM;
    }

    return ERR_NONE;
}