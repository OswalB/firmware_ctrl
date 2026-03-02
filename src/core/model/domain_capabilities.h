#pragma once

#include <stdint.h>
#include "core/model/domain_types.h"
#include "core/model/param_types.h"

typedef struct
{
    int32_t min;
    int32_t max;
    bool has_range;
} ParamRange;

typedef struct {
    uint8_t min;
    uint8_t max;
    bool has_range;
} InstanceRange;

typedef struct
{
    DomainType domain;
    uint32_t supported_params_mask;
    uint32_t supported_cmds_mask;
    ParamRange param_ranges[PARAM_COUNT];
    InstanceRange id_range;
} DomainCapabilities;

const DomainCapabilities *get_domain_capabilities(DomainType domain);
bool validate_domain_capabilities_table(void);