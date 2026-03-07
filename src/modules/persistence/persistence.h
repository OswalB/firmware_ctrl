#pragma once

#include "config_slot.h"

#define SLOT_A_ADDR 0
#define SLOT_B_ADDR sizeof(ConfigSlot)

void persistence_init(void);
//bool persistence_load(MachineConfig *config);
bool persistence_Load(ConfigSlot *out);
void persistence_save(const MachineConfig *config);

