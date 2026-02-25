#pragma once

//#include <stdint.h>

/* ===== Inicialización ===== */
void serial_init(void);

/* ===== Actualización periódica ===== */
void serial_update(void);
void serial_drain_fsm(void);

/* ===== Salida básica ===== */
void serial_write(const char *msg);
void serial_writeln(const char *msg);
