#include "persist.h"
#include "../console/console.h"

#define EEPROM_TOTAL_BYTES 4096
#define EEPROM_SLOT_SIZE   (EEPROM_TOTAL_BYTES / 2)

#define CONFIG_MAGIC   0xA55A5AA5
#define CONFIG_VERSION 0x0001

typedef struct
{
    uint32_t magic;
    uint16_t version;
    uint16_t size;
    uint32_t generation;

} ConfigHeader;


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


typedef struct
{
    ConfigHeader header;
    MachineConfig config;
    uint32_t crc;

} ConfigSlot;

static_assert(sizeof(ConfigSlot) <= EEPROM_SLOT_SIZE,
              "ConfigSlot exceeds EEPROM slot size");


bool persist_init(void)
{
    Console_Print(MSG_LOG, "Persist module init");
    return true;
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