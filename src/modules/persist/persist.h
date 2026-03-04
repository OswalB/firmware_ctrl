#ifndef PERSIST_H
#define PERSIST_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

bool persist_init(void);

size_t persist_get_slot_size(void);
size_t persist_get_config_size(void);
size_t persist_get_remaining_bytes(void);

#ifdef __cplusplus
}
#endif

#endif