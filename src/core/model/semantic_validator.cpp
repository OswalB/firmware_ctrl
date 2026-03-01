#include "semantic_validator.h"
#include "core/model/event_types.h"
#include "domain_capabilities.h"
#include "core/model/domain_types.h"
#include "core/model/param_types.h"
#include "core/model/response_types.h"

Response validate_semantics(Event *ev)
{
    if (!ev)
        return {RESP_ERR_EVENT, "Event error"};

    const DomainCapabilities *caps =
        get_domain_capabilities(ev->domain);

    if (!caps)
        return {RESP_ERR_COMMAND, "Domain error"};

    // 1️⃣ Validar comando permitido
    if (!(caps->supported_cmds_mask & (1u << ev->type)))
        return {RESP_ERR_COMMAND, "Command error"};

    // 2️⃣ Validar parámetro (si existe)
    if (ev->param < PARAM_COUNT)
    {
        if (ev->param != 0) // 0 significa "no param" en tu diseño actual
        {
            if (!(caps->supported_params_mask & (1u << ev->param)))
                return {RESP_ERR_COMMAND, "Param error"};
        }
    }

    // validar rangos
    if (ev->param != PARAM_UNKNOW)
    {
        if (!(caps->supported_params_mask & (1u << ev->param)))
            return {RESP_ERR_COMMAND, "Value out of range"};

        int32_t value = ev->value;

        ParamRange range = caps->param_ranges[ev->param];

        if (value < range.min || value > range.max)
            return {RESP_ERR_COMMAND, "Value error"};
    }

    return {RESP_OK, ""};
}