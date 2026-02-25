#include "app_run.h"
#include "core/fsm/machine.h"
//#include "modules/led/led.h"
#include "input/serial/serial_if.h"
void app_run()
{
    serial_update();
    machine_update();
    serial_drain_fsm();  // imprime todo lo que FSM haya producido
    //led_update();
}
