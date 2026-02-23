//#include "core/event/event_queue.h"
//#include "modules/led/led.h"
#include "input/serial/serial_if.h"
//#include "core/fsm/machine.h"
//#include "modules/motor/motor.h"

void app_init()
{
    //eventQueue_init();
    //led_init();
    serial_init();
    //machine_init();
    serial_writeln("=== Firmaware V1.0 ===");
    // motorSystem_init();
}