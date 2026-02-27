#pragma once

//#include <stdint.h>

typedef enum
{
    CONS_IDLE,
    CONS_BUSY,
    CONS_READY  
}Console_status;

void set_stateConsole(Console_status st);

/* ===== Inicialización ===== */
void serial_init(void);

/* ===== Actualización periódica ===== */
void serial_update(void);
void serial_drain_fsm(void);

/* ===== Salida básica ===== */
void serial_write(const char *msg);
void serial_writeln(const char *msg);
