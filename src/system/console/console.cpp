#include "console.h"
#include "platform/transport/transport.h"
#include <stdarg.h>
#include <stdio.h>
#include "input/serial/serial_if.h"

static ConsoleMode g_consoleMode = CONSOLE_NONE;

void Console_SetMode(ConsoleMode mode)
{
    g_consoleMode = mode;
}

static const char* messagePrefix(MessageType type)
{
    switch (type)
    {
        case MSG_LOG:   return "[LOG] ";
        case MSG_DBG:   return "[DBG] ";
        case MSG_ERR:   return "[ERR] ";
        case MSG_FORCE: return "[FRC] ";
        default:        return "";
    }
}

static bool shouldPrint(MessageType type)
{
    if (type == MSG_FORCE)
        return true;

    switch (g_consoleMode)
    {
        case CONSOLE_NONE:
            return false;

        case CONSOLE_LOG:
            return type == MSG_LOG;

        case CONSOLE_DBG:
            return type == MSG_DBG;

        case CONSOLE_ERR:
            return type == MSG_ERR;

        case CONSOLE_ALL:
            return true;

        default:
            return false;
    }
}

void Console_Print(MessageType type, const char *format, ...)
{
    if (!shouldPrint(type))
        return;

    char buffer[128];
    char finalBuffer[160];  // espacio extra para prefijo

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    const char* prefix = messagePrefix(type);

    snprintf(finalBuffer, sizeof(finalBuffer), "%s%s", prefix, buffer);

    Transport_Write(finalBuffer);
    set_stateConsole(CONS_BUSY);
}
