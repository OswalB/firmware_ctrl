#pragma once

#include "config_slot.h"

#define SLOT_A_ADDR 0
#define SLOT_B_ADDR sizeof(ConfigSlot)

void persistence_init(void);
bool persistence_load(MachineConfig *out);
void persistence_save(const MachineConfig *config);

// Desde los modulos:

MachineConfig* machine_config_mutable(void);

const MachineConfig* machine_config_get(void);

MachineConfig* machine_config_edit(void);

void machine_config_mark_dirty(void);

bool machine_config_save(void);
