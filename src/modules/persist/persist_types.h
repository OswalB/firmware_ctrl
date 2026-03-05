#ifndef PERSIST_TYPES_H
#define PERSIST_TYPES_H

#include <stdint.h>

#define MAX_MODULES 16
#define MODE_TABLE_SIZE 128

typedef struct
{
    uint16_t max_speed;
    uint16_t min_speed;

    uint8_t  module_enabled[MAX_MODULES];
    uint16_t module_limit[MAX_MODULES];

    uint8_t  mode_table[MODE_TABLE_SIZE];

} MachineConfig;

#endif