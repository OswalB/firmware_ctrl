#pragma once

typedef enum {
    CONSOLE_NONE = 0,
    CONSOLE_LOG,
    CONSOLE_DBG,
    CONSOLE_LYD
} ConsoleMode;

typedef enum {
    MSG_LOG,
    MSG_DBG,
    MSG_FORCE
} MessageType;

void Console_SetMode(ConsoleMode mode);
void Console_Print(MessageType type, const char *format, ...);