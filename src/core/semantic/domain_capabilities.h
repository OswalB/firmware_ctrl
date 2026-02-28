#pragma once

#include <stdint.h>
#include "core/types/domain_types.h"
#include "core/types/param_types.h"


typedef struct
{
    int32_t min;
    int32_t max;
    bool has_range;
} ParamRange;

typedef struct
{
    DomainType domain;
    uint32_t supported_params_mask;
    uint32_t supported_cmds_mask;
    ParamRange param_ranges[PARAM_COUNT];
} DomainCapabilities;



const DomainCapabilities *get_domain_capabilities(DomainType domain);
bool validate_domain_capabilities_table(void);