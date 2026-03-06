#include "eeprom_driver.h"
#include <avr/eeprom.h>

void eeprom_write_bytes(uint16_t addr, const uint8_t *data, size_t len)
{
    eeprom_update_block(data, (void*)addr, len);
}

void eeprom_read_bytes(uint16_t addr, uint8_t *data, size_t len)
{
    eeprom_read_block(data, (const void*)addr, len);
}


