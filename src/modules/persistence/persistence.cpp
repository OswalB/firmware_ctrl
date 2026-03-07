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

static bool persistence_validate(const ConfigSlot *slot);
bool persistence_load(MachineConfig *out);

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

void persistence_save(const MachineConfig *config)
{
    ConfigSlot a;
    ConfigSlot b;
    ConfigSlot slot;

    eeprom_read_bytes(SLOT_A_ADDR, (uint8_t *)&a, sizeof(ConfigSlot));
    eeprom_read_bytes(SLOT_B_ADDR, (uint8_t *)&b, sizeof(ConfigSlot));

    bool validA = persistence_validate(&a);
    bool validB = persistence_validate(&b);

    uint32_t next_counter = 1;
    uint16_t write_addr;

    if (validA && validB)
    {
        if (a.header.counter >= b.header.counter)
        {
            next_counter = a.header.counter + 1;
            write_addr = SLOT_B_ADDR;
        }
        else
        {
            next_counter = b.header.counter + 1;
            write_addr = SLOT_A_ADDR;
        }
    }
    else if (validA)
    {
        next_counter = a.header.counter + 1;
        write_addr = SLOT_B_ADDR;
    }
    else if (validB)
    {
        next_counter = b.header.counter + 1;
        write_addr = SLOT_A_ADDR;
    }
    else
    {
        next_counter = 1;
        write_addr = SLOT_A_ADDR;
    }

    slot.header.magic = CONFIG_MAGIC;
    slot.header.version = CONFIG_VERSION;
    slot.header.size = sizeof(MachineConfig);
    slot.header.counter = next_counter;

    slot.config = *config;

    slot.crc = crc32_compute((uint8_t *)&slot.config, sizeof(MachineConfig));

    eeprom_write_bytes(write_addr, (uint8_t *)&slot, sizeof(ConfigSlot));

    Console_Print(MSG_LOG, "Config saved (counter=%lu)", next_counter);
}

static bool persistence_validate(const ConfigSlot *slot)
{
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

    if (slot->header.size != sizeof(MachineConfig))
    {
        Console_Print(MSG_DBG, "Invalid config size");
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


