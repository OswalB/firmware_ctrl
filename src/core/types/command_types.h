#pragma once

typedef enum
{
    CMD_UNKNOWN = 0,
    CMD_SET,
    CMD_GET,
    CMD_STATUS,
    CMD_RESET
} CommandType;