#include "machine_config.h"

void machine_config_set_defaults(MachineConfig *cfg)
{
    cfg->motor_max_speed = 120;
    cfg->motor_acceleration = 500;
    cfg->sensor_enabled = 1;
    cfg->Led1_time=10500;
}