#pragma once

//#include <stdint.h>
#include "core/model/event_types.h"
#include "core/event/event_queue.h"

typedef enum
{
    CONS_IDLE,
    CONS_BUSY,
    CONS_READY  
}Console_status;

typedef enum
{
    ANSI_IDLE,
    ANSI_ESC,
    ANSI_BRACKET,
    ANSI_NUMBER
} AnsiState;

static AnsiState ansiState = ANSI_IDLE;
static uint8_t ansiValue = 0;

void set_stateConsole(Console_status st);

/* ===== Inicialización ===== */
void serial_init(void);

/* ===== Actualización periódica ===== */
void serial_update(void);
void serial_drain_fsm(void);

/* ===== Salida básica ===== */
void serial_write(const char *msg);
void serial_writeln(const char *msg);
