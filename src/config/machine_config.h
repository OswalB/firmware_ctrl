#pragma once

#include <stdint.h>

#define CONFIG_MAGIC 0x43464731 // "CFG1"
#define CONFIG_VERSION 1

static bool config_dirty = false;

typedef struct
{
    uint8_t motor_max_speed;
    uint16_t motor_acceleration;
    uint8_t sensor_enabled;
    uint16_t Led1_time;

} MachineConfig;



void machine_config_set_defaults(MachineConfig *cfg);
