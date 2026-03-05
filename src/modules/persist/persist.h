#ifndef PERSIST_H
#define PERSIST_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "persist_types.h"

#ifdef __cplusplus
extern "C" {
#endif



bool persist_init(void);

size_t persist_get_slot_size(void);
size_t persist_get_config_size(void);
size_t persist_get_remaining_bytes(void);
MachineConfig* persist_get_config(void);
void persist_load_defaults(void);
void persist_debug_build_slot(void);
void persist_save_slotA(void);

#ifdef __cplusplus
}
#endif



#endif