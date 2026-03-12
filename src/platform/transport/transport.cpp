#include <Arduino.h>
#include <stdarg.h>

void Transport_Send(const char *format, ...)
{
    char buffer[128];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    Serial.println(buffer);
}

void Transport_Writeln(const char* msg)
{
    Serial.println(msg);
}

void Transport_Write(const char* msg)
{
    Serial.print(msg);
}