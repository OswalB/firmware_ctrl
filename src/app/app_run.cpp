#include "app_run.h"
#include "core/fsm/machine.h"
#include "modules/led/led_module.h"
#include "input/serial/serial_if.h"
#include "lib/menu/menu.h"
#include "input/encoder/encoder.h"
#include "drivers/buzzer/buzzer.h"

void app_run()
{
    serial_update();
    encoder_update();
    machine_update();
    menu_update();
    buzzer_tick;
    serial_drain_fsm(); // imprime todo lo que FSM haya producido
    led::led_update();
}
