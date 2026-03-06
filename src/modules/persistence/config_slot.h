#pragma once

#include <stdint.h>
#include "config/machine_config.h"

#define CONFIG_MAGIC 0x43464731  // "CFG1"

typedef struct
{
    uint32_t magic;
    uint16_t version;
    uint16_t size;

} ConfigHeader;

typedef struct
{
    ConfigHeader header;
    MachineConfig config;
    uint32_t crc;

} ConfigSlot;
