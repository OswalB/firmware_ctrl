#include "app_run.h"
//#include "core/fsm/machine.h"
//#include "modules/led/led.h"
#include "input/serial/serial_if.h"
void app_run()
{
    serial_update();
    //machine_update();
    //led_update();
}
