//#include "core/event/event_queue.h"
//#include "modules/led/led.h"
#include "input/serial/serial_if.h"
#include "core/fsm/machine.h"
//#include "modules/motor/motor.h"
#include "system/console/console.h"
#include "system/system.h"

void app_init()
{
    //eventQueue_init();
    //led_init();
    serial_init();
    serial_writeln("=== Firmaware V1.0 ===");
    system_init();
    machine_init();
    
    Console_SetMode(CONSOLE_ALL);
    

    
    // motorSystem_init();
}