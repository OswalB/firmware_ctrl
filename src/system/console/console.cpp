#include "console.h"
#include "platform/transport/transport.h"
#include <stdarg.h>
#include <stdio.h>

static ConsoleMode g_consoleMode = CONSOLE_NONE;

void Console_SetMode(ConsoleMode mode)
{
    g_consoleMode = mode;
}

void Console_Print(MessageType type, const char *format, ...)
{
    if (type != MSG_FORCE)
    {
        if (g_consoleMode == CONSOLE_NONE)
            return;

        if (g_consoleMode == CONSOLE_LOG && type != MSG_LOG)
            return;

        if (g_consoleMode == CONSOLE_DBG && type != MSG_DBG)
            return;
    }

    char buffer[128];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    Transport_Write(buffer);
}
