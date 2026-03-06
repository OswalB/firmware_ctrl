#pragma once

#include <stdint.h>

typedef struct
{
    uint8_t  motor_max_speed;
    uint16_t motor_acceleration;
    uint8_t  sensor_enabled;

} MachineConfig;

