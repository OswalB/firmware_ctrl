// #include "core/event/event_queue.h"
#include "modules/led/led_module.h"
#include "input/serial/serial_if.h"
#include "core/fsm/machine.h"
// #include "modules/motor/motor.h"
#include "modules/console/console.h"
#include "modules/system/system.h"
#include "modules/persistence/persistence .h"


void app_init()
{
       
    // eventQueue_init();
    led::led_init();

    Console_SetMode(CONSOLE_ALL);
    serial_init();
    serial_writeln("=== Firmaware V1.005 ===");

    persistence_init();

    machine_init();
    system_init();
    
    // motorSystem_init();
}