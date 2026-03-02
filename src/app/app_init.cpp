// #include "core/event/event_queue.h"
// #include "modules/led/led.h"
#include "input/serial/serial_if.h"
#include "core/fsm/machine.h"
// #include "modules/motor/motor.h"
#include "modules/console/console.h"
#include "modules/system/system.h"

void app_init()
{
    // eventQueue_init();
    // led_init();
    Console_SetMode(CONSOLE_ALL);
    serial_init();
    serial_writeln("=== Firmaware V1.003 ===");

    machine_init();
    system_init();

    // motorSystem_init();
}