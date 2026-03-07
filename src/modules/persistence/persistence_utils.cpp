#include <avr/eeprom.h>
#include "persistence_utils.h"
#include "modules/console/console.h"

#define EEPROM_TOTAL_SIZE 4096

void Persistence_PrintLayout(uint16_t slot_size)
{
    uint16_t total = EEPROM_TOTAL_SIZE;

    uint16_t slots = total / slot_size;

    uint16_t used_bytes = slots * slot_size;

    uint16_t remaining = total - used_bytes;

    Console_Print(MSG_LOG, "EEPROM Layout");
    Console_Print(MSG_LOG, "-------------");
    Console_Print(MSG_LOG, "EEPROM total=%u", total);
    Console_Print(MSG_LOG, "Slot size=%u", slot_size);
    Console_Print(MSG_LOG, "Slots available=%u", slots);
    Console_Print(MSG_LOG, "Bytes used by slots=%u", used_bytes);
    Console_Print(MSG_LOG, "Remaining bytes=%u", remaining);
}

void Persistence_PrintUsage(uint16_t slot_size)
{
    uint16_t total = EEPROM_TOTAL_SIZE;
    uint16_t slots = total / slot_size;
    uint16_t used  = slots * slot_size;
    uint16_t free  = total - used;

    Console_Print(MSG_LOG, "EEPROM total=%u", total);
    Console_Print(MSG_LOG, "Slot size=%u", slot_size);
    Console_Print(MSG_LOG, "Slots available=%u", slots);
    Console_Print(MSG_LOG, "Bytes used=%u", used);
    Console_Print(MSG_LOG, "Bytes free=%u", free);
}