#pragma once

typedef enum {
    CONSOLE_NONE = 0,
    CONSOLE_LOG,    
    CONSOLE_DBG,
    CONSOLE_ALL,
    CONSOLE_ERR
} ConsoleMode;

typedef enum {
    MSG_NONE =0,
    MSG_LOG,
    MSG_DBG,
    MSG_FORCE,
    MSG_ERR,
    
} MessageType;

void Console_SetMode(ConsoleMode mode);
void Console_Print(MessageType type, const char *format, ...);