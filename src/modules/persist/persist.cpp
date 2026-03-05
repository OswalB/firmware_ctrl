#include <EEPROM.h>
#include "persist.h"
#include "../console/console.h"

#define EEPROM_TOTAL_BYTES 4096
#define EEPROM_SLOT_SIZE (EEPROM_TOTAL_BYTES / 2)

#define CONFIG_MAGIC 0xA55A5AA5
#define CONFIG_VERSION 0x0001

#define EEPROM_SLOT_A_ADDR 0
#define EEPROM_SLOT_B_ADDR (EEPROM_SLOT_A_ADDR + EEPROM_SLOT_SIZE)

typedef struct
{
    uint32_t magic;
    uint16_t version;
    uint16_t size;
    uint32_t generation;

} ConfigHeader;

typedef struct
{
    ConfigHeader header;
    MachineConfig config;
    uint32_t crc;

} ConfigSlot;

static MachineConfig g_config;

static_assert(sizeof(ConfigSlot) <= EEPROM_SLOT_SIZE,
              "ConfigSlot exceeds EEPROM slot size");

static uint32_t g_generation = 0;

//------ FORWARDS -------
// static bool persist_load_slot(uint16_t addr, ConfigSlot *out_slot);
static uint32_t crc32_compute(const uint8_t *data, size_t length);
static bool persist_validate_slot(const ConfigSlot *slot);
static bool persist_read_slot(uint16_t addr, ConfigSlot *slot);
static bool persist_write_slot(uint16_t addr);
// ----------------------

bool persist_init(void)
{
    Console_Print(MSG_LOG, "*** Persist module init ***");

    ConfigSlot slotA;
    ConfigSlot slotB;

    bool validA = persist_read_slot(EEPROM_SLOT_A_ADDR, &slotA);
    bool validB = persist_read_slot(EEPROM_SLOT_B_ADDR, &slotB);

    if (validA)
    {
        g_config = slotA.config;
        g_generation = slotA.header.generation;

        Console_Print(MSG_LOG, "Slot A loaded");
        return true;
    }

    if (validB)
    {
        g_config = slotB.config;
        g_generation = slotB.header.generation;

        Console_Print(MSG_LOG, "Slot B loaded");
        return true;

        Console_Print(MSG_LOG, "Stored CRC: %08X", header->crc);
        Console_Print(MSG_LOG, "Calc CRC:   %08X", crc_check);
    }

    Console_Print(MSG_LOG, "No valid slots");

    persist_load_defaults();
    persist_write_slot(EEPROM_SLOT_A_ADDR);

    return true;
}

static void persist_build_slot(ConfigSlot *slot)
{
    slot->header.magic = CONFIG_MAGIC;
    slot->header.version = CONFIG_VERSION;
    slot->header.size = sizeof(ConfigSlot);
    slot->header.generation = ++g_generation;

    slot->config = g_config;
    /*
        size_t crc_length = sizeof(ConfigHeader) + sizeof(MachineConfig);

        slot->crc = crc32_compute(
            (uint8_t*)slot,
            crc_length
        );*/
    slot->crc = crc32_compute(
        (uint8_t *)slot,
        sizeof(ConfigSlot) - sizeof(uint32_t));
}

static bool persist_read_slot(uint16_t addr, ConfigSlot *slot)
{
    eeprom_read_block(
        addr,
        (uint8_t *)slot,
        sizeof(ConfigSlot));

    return persist_validate_slot(slot);
}

static bool persist_write_slot(uint16_t addr)
{
    ConfigSlot slot;

    persist_build_slot(&slot);

    Console_Print(MSG_LOG, "Writing slot @ %u", addr);

    eeprom_write_block(
        addr,
        (uint8_t *)&slot,
        sizeof(ConfigSlot));

    ConfigSlot verify;

    eeprom_read_block(
        addr,
        (uint8_t *)&verify,
        sizeof(ConfigSlot));

    /*size_t crc_length = sizeof(ConfigHeader) + sizeof(MachineConfig);

    uint32_t crc_check = crc32_compute(
        (uint8_t*)&verify,
        crc_length
    );*/
    size_t crc_length = sizeof(ConfigSlot) - sizeof(uint32_t);

    uint32_t crc_check = crc32_compute(
        (const uint8_t *)&verify,
        crc_length);

    if (crc_check == verify.crc)
    {
        Console_Print(MSG_LOG, "Verification OK");
        return true;
    }

    Console_Print(MSG_ERR, "Verification FAILED");
    return false;
}

size_t persist_get_slot_size(void)
{
    return EEPROM_SLOT_SIZE;
}

size_t persist_get_config_size(void)
{
    return sizeof(ConfigSlot);
}

size_t persist_get_remaining_bytes(void)
{
    return EEPROM_SLOT_SIZE - sizeof(ConfigSlot);
}

MachineConfig *persist_get_config(void)
{
    return &g_config;
}

void persist_load_defaults(void)
{
    g_config.max_speed = 100;
    g_config.min_speed = 10;

    for (int i = 0; i < MAX_MODULES; i++)
    {
        g_config.module_enabled[i] = 0;
        g_config.module_limit[i] = 50;
    }

    for (int i = 0; i < MODE_TABLE_SIZE; i++)
    {
        g_config.mode_table[i] = 0;
    }

    Console_Print(MSG_LOG, "Defaults loaded into RAM config");
}

static uint32_t crc32_compute(const uint8_t *data, size_t length)
{
    uint32_t crc = 0xFFFFFFFF;

    for (size_t i = 0; i < length; i++)
    {
        crc ^= data[i];

        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }

    return ~crc;
}

static void eeprom_write_block(uint16_t addr, const uint8_t *data, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        EEPROM.update(addr + i, data[i]);
    }
}

static void eeprom_read_block(uint16_t addr, uint8_t *data, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        data[i] = EEPROM.read(addr + i);
    }
}

void persist_save_slotA(void)
{
    persist_write_slot(EEPROM_SLOT_A_ADDR);
}

void persist_save_slotB(void)
{
    persist_write_slot(EEPROM_SLOT_B_ADDR);
}

static bool persist_validate_slot(const ConfigSlot *slot)
{
    if (slot->header.magic != CONFIG_MAGIC)
        return false;

    if (slot->header.version != CONFIG_VERSION)
        return false;

    if (slot->header.size != sizeof(ConfigSlot))
        return false;

    /*size_t crc_length = sizeof(ConfigHeader) + sizeof(MachineConfig);

    uint32_t crc_check = crc32_compute(
        (const uint8_t *)slot,
        crc_length);*/

    size_t crc_length = sizeof(ConfigSlot) - sizeof(uint32_t);

    uint32_t crc_check = crc32_compute(
        (const uint8_t *)slot,
        crc_length);

    if (crc_check != slot->crc)
        return false;

    return true;
}
