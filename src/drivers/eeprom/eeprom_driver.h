#pragma once

#include <stdint.h>
#include <stddef.h>

void eeprom_write_bytes(uint16_t addr, const uint8_t *data, size_t len);
void eeprom_read_bytes(uint16_t addr, uint8_t *data, size_t len);
