#pragma once

#include <stdint.h>
#include "config/machine_config.h"



typedef struct
{
    uint32_t magic;
    uint16_t version;
    uint16_t size;
    uint32_t counter;

} ConfigHeader;

typedef struct
{
    ConfigHeader header;
    MachineConfig config;
    uint32_t crc;

} ConfigSlot;
