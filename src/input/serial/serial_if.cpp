#include <Arduino.h>
#include "input/serial/serial_if.h"
//#include "input/command/parser.h"

#define SERIAL_BAUDRATE 115200
#define RX_BUFFER_SIZE 128

/* ===== Buffer interno ===== */

static char rxBuffer[RX_BUFFER_SIZE];
static uint8_t rxIndex = 0;

/* ===== Prototipos privados ===== */

void serial_init(void)
{
  Serial.begin(SERIAL_BAUDRATE);
}

void serial_update(void)
{
  while (Serial.available())

  {
    char c = Serial.read();
    if (c == 8 || c == 127)
    {
      if (rxIndex > 0)
      {
        rxIndex--;
        Serial.print("\b \b");
      }
    }
    else
    {
      Serial.write(c);

      if (c == '\r' || c == '\n')
      {
        if (rxIndex > 0)
        {
          rxBuffer[rxIndex] = '\0'; // Termina string
          serial_writeln("\r");
          //parser_parse(rxBuffer); // Llama parser
          serial_writeln(rxBuffer);
          rxIndex = 0;            // Reset buffer
        }
      }
      else
      {
        if (rxIndex < RX_BUFFER_SIZE - 1)
        {
          rxBuffer[rxIndex++] = c;
        }
        else
        {
          rxIndex = 0;
        }
      }
    }
  }
}

void serial_write(const char *msg)
{
  Serial.print(msg);
}

void serial_writeln(const char *msg)
{
  Serial.println(msg);
}
