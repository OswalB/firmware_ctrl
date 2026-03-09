#include "machine_config.h"
#include "lib/utils/utils.h"

void machine_config_set_defaults(MachineConfig *cfg)
{   
    utils_strcopy_safe(cfg->customer[0], "--", sizeof(cfg->customer[0]));
    cfg->motor_max_speed = 120;
    cfg->motor_acceleration = 500;
    cfg->sensor_enabled = 1;
    cfg->Led1_time=10500;
}