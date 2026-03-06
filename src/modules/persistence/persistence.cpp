#include "drivers/eeprom/eeprom_driver.h"
#include "modules/console/console.h"
#include "config/machine_config.h"
#include "persistence.h"
#include "config_slot.h"
#include "lib/crc32/crc32.h"

//-----------------------------------------
//---- FORWARDS
//-----------------------------------------

void persistence_init(void)
{
    Console_Print(MSG_DBG, "EEPROM init:");
    MachineConfig cfg;

    if (persistence_load(&cfg))
    {
        Console_Print(MSG_LOG, "Using stored configuration");
    }
    else
    {
        Console_Print(MSG_LOG, "Loading defaults");

        cfg.motor_max_speed = 120;
        cfg.motor_acceleration = 500;
        cfg.sensor_enabled = 1;

        persistence_save(&cfg);
    }
}

void persistence_save(const MachineConfig *config)
{
    ConfigSlot slot;

    slot.header.magic = CONFIG_MAGIC;
    slot.header.version = 1;
    slot.header.size = sizeof(MachineConfig);

    slot.config = *config;

    slot.crc = crc32_compute((uint8_t *)&slot.config, sizeof(MachineConfig));

    eeprom_write_bytes(SLOT_A_ADDR, (uint8_t *)&slot, sizeof(ConfigSlot));

    Console_Print(MSG_LOG, "Config saved to EEPROM");
}

bool persistence_load(MachineConfig *config)
{
    ConfigSlot slot;

    eeprom_read_bytes(SLOT_A_ADDR, (uint8_t *)&slot, sizeof(ConfigSlot));

    if (slot.header.magic != CONFIG_MAGIC)
    {
        Console_Print(MSG_ERR, "Invalid magic");
        return false;
    }

    if (slot.header.size != sizeof(MachineConfig))
    {
        Console_Print(MSG_ERR, "Invalid config size");
        return false;
    }

    uint32_t crc = crc32_compute((uint8_t *)&slot.config, sizeof(MachineConfig));

    if (crc != slot.crc)
    {
        Console_Print(MSG_ERR, "CRC mismatch");
        return false;
    }

    *config = slot.config;

    Console_Print(MSG_LOG, "Config loaded OK");

    return true;
}

//-----------------------------------------
//---- TESTS VERIFY
//-----------------------------------------
