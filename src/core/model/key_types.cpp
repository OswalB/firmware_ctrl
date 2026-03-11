#include <stddef.h>
#include "key_types.h"

extern const EnumEntry key_table_enum[] = {
    {"key none", KEY_NONE},
    {"key up", KEY_UP},
    {"key down", KEY_DOWN},
    {"key left", KEY_LEFT},
    {"key right", KEY_RIGHT},
    {"key home", KEY_HOME},
    {"key end", KEY_END},
    {"key delete", KEY_DELETE},
    {"key F1", KEY_F1},
    {"key F2", KEY_F2},
    {"key F3", KEY_F3},
    {"key F4", KEY_F4},
    {"key F5", KEY_F5},
    {"key F6", KEY_F6},
    {"key F7", KEY_F7},
    {"key F8", KEY_F8},
    {"key F9", KEY_F9},
    {"key F10", KEY_F10},
    {"key F11", KEY_F11},
    {"key F12", KEY_F12}

};

const size_t key_table_count =
    sizeof(key_table_enum) / sizeof(key_table_enum[0]);