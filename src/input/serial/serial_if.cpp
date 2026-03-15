#include <Arduino.h>
#include "input/serial/serial_if.h"
#include "input/command/parser.h"
#include "core/fsm/machine.h"
#include "modules/console/console.h"
#include "core/model/key_types.h"

#define SERIAL_BAUDRATE 115200
#define RX_BUFFER_SIZE 128

/* ===== Buffer interno ===== */

static char rxBuffer[RX_BUFFER_SIZE];
static uint8_t rxIndex = 0;
Console_status g_consoleStatus = CONS_BUSY;

/* ===== Prototipos privados ===== */

KeyCode ansi_decode(char c);

void serial_init(void)
{
  Serial.begin(SERIAL_BAUDRATE);
  g_consoleStatus = CONS_BUSY;
}

void serial_update(void)
{
  while (Serial.available())

  {
    char c = Serial.read();

    KeyCode key = ansi_decode(c);

    if (key != KEY_NONE)
    {
      // event_send(EVT_KEY_PRESS, key);
      //Console_Print(MSG_DBG, "Key= %d", key);
      Event ev ={};
      ev.type = EVT_KEY_PRESS;
      ev.value = key;

      eventQueue_push(ev);

      rxIndex = 0;
      continue;
    }
    
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
          parser_parse_line(rxBuffer); // Llama parser

          if (fsm_getState() == MS_IDLE)
          {
            // serial_write(">> ");
          }
          rxIndex = 0; // Reset buffer
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

void serial_drain_fsm(void)
{
  while (fsm_hasOutput())
  {
    Response r = fsm_getOutput();

    switch (r.type)
    {
    case RESP_OK:
      serial_writeln("ok");
      break;

    case RESP_ERROR:
      Console_Print(MSG_ERR, r.text);
      break;

    case RESP_FAULT:
      serial_write("SYSTEM FAULT - ");
      serial_writeln(r.text);
      break;

    case RESP_INFO:
      serial_writeln(r.text);
      break;
    default:
      break;
    }
  }

  if (g_consoleStatus == CONS_BUSY)
  {
    serial_write(">> ");
    g_consoleStatus = CONS_READY;
  }
}

void set_stateConsole(Console_status st)
{
  g_consoleStatus = st;
}

KeyCode ansi_decode(char c)
{
  switch (ansiState)
  {

  case ANSI_IDLE:

    if (c == 27) // ESC
    {
      ansiState = ANSI_ESC;
      return KEY_NONE;
    }

    return KEY_NONE;

  case ANSI_ESC:

    if (c == '[')
    {
      ansiState = ANSI_BRACKET;
      return KEY_NONE;
    }

    if (c == 'O')
    {
      ansiState = ANSI_BRACKET;
      return KEY_NONE;
    }

    ansiState = ANSI_IDLE;
    return KEY_NONE;

  case ANSI_BRACKET:

    if (c >= '0' && c <= '9')
    {
      ansiValue = c - '0';
      ansiState = ANSI_NUMBER;
      return KEY_NONE;
    }

    ansiState = ANSI_IDLE;

    switch (c)
    {
    case 'A':
      return KEY_UP;
    case 'B':
      return KEY_DOWN;
    case 'C':
      return KEY_RIGHT;
    case 'D':
      return KEY_LEFT;
    case 'H':
      return KEY_HOME;
    case 'F':
      return KEY_END;
    }

    return KEY_NONE;

  case ANSI_NUMBER:

    if (c >= '0' && c <= '9')
    {
      ansiValue = ansiValue * 10 + (c - '0');
      return KEY_NONE;
    }

    if (c == '~')
    {
      ansiState = ANSI_IDLE;

      switch (ansiValue)
      {
      case 3:
        return KEY_DELETE;
      case 15:
        return KEY_F5;
      case 17:
        return KEY_F6;
      case 18:
        return KEY_F7;
      case 19:
        return KEY_F8;
      case 20:
        return KEY_F9;
      case 21:
        return KEY_F10;
      case 23:
        return KEY_F11;
      case 24:
        return KEY_F12;
      }
    }

    ansiState = ANSI_IDLE;
    return KEY_NONE;
  }

  ansiState = ANSI_IDLE;
  return KEY_NONE;
}