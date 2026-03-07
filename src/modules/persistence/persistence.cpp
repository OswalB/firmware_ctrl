#include "drivers/eeprom/eeprom_driver.h"
#include "modules/console/console.h"
#include "config/machine_config.h"
#include "persistence.h"
#include "config_slot.h"
#include "lib/crc32/crc32.h"
#include "persistence_utils.h"

//-----------------------------------------
//---- FORWARDS
//-----------------------------------------

bool persistence_validate(const ConfigSlot *slot);
bool persistence_load(MachineConfig *out);
void persistence_save(ConfigSlot *slot);

//------------------------------------------

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
    Persistence_PrintLayout(sizeof(ConfigSlot));
}

void persistence_save(const MachineConfig *config)
{
    ConfigSlot slot;

    slot.header.magic = CONFIG_MAGIC;
    slot.header.version = CONFIG_VERSION;
    slot.header.size = sizeof(MachineConfig);
    slot.header.counter = 0;

    slot.config = *config;

    slot.crc = crc32_compute((uint8_t *)&slot.config, sizeof(MachineConfig));

    persistence_save(&slot);

    Console_Print(MSG_LOG, "Config saved to EEPROM");
}

bool persistence_load(MachineConfig *out)
{
    ConfigSlot a;
    ConfigSlot b;
    eeprom_read_bytes(SLOT_A_ADDR, (uint8_t *)&a, sizeof(ConfigSlot));
    eeprom_read_bytes(SLOT_B_ADDR, (uint8_t *)&b, sizeof(ConfigSlot));

    bool validA = persistence_validate(&a);
    bool validB = persistence_validate(&b);

    if (validA && validB)
    {
        if (a.header.counter >= b.header.counter)
            *out = a.config;
        else
            *out = b.config;

        return true;
    }

    if (validA)
    {
        *out = a.config;
        return true;
    }

    if (validB)
    {
        *out = b.config;
        return true;
    }

    return false;
}

void persistence_save(ConfigSlot *slot)
{
    ConfigSlot a;
    ConfigSlot b;

    eeprom_read_bytes(SLOT_A_ADDR, (uint8_t *)&a, sizeof(ConfigSlot));
    eeprom_read_bytes(SLOT_B_ADDR, (uint8_t *)&b, sizeof(ConfigSlot));

    bool validA = persistence_validate(&a);
    bool validB = persistence_validate(&b);

    uint16_t addr;

    if (validA && validB)
    {
        if (a.header.counter >= b.header.counter)
            addr = SLOT_B_ADDR;
        else
            addr = SLOT_A_ADDR;
    }
    else if (validA)
    {
        addr = SLOT_B_ADDR;
    }
    else
    {
        addr = SLOT_A_ADDR;
    }

    eeprom_write_bytes(addr, (uint8_t *)slot, sizeof(ConfigSlot));
}

bool persistence_validate(const ConfigSlot *slot)
{
    if (slot->header.size != sizeof(MachineConfig))
    {
        Console_Print(MSG_DBG, "Invalid config size");
        return false;
    }

    if (slot->header.magic != CONFIG_MAGIC)
    {
        Console_Print(MSG_DBG, "Invalid magic");
        return false;
    }

    if (slot->header.version != CONFIG_VERSION)
    {
        Console_Print(MSG_DBG, "Invalid version");
        return false;
    }

    uint32_t crc_calc = crc32_compute(
        (const uint8_t *)&slot->config,
        sizeof(MachineConfig));

    if (crc_calc != slot->crc)
    {
        Console_Print(MSG_DBG, "CRC mismatch");
        return false;
    }

    return true;
}

//-----------------------------------------
//---- TESTS VERIFY
//-----------------------------------------
