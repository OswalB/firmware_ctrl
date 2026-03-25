// #include "core/event/event_queue.h"
#include "modules/led/led_module.h"
#include "input/serial/serial_if.h"
#include "core/fsm/machine.h"
// #include "modules/motor/motor.h"
#include "modules/console/console.h"
#include "modules/system/system.h"
#include "modules/persistence/persistence.h"
#include "modules/display/display.h"
#include "lib/crc32/crc32.h"
#include "lib/menu/menu.h"
#include "input/encoder/encoder.h"

void app_init()
{
       
    // eventQueue_init();
    led::led_init();

    Console_SetMode(CONSOLE_ALL);
    serial_init();
    serial_writeln("=== Firmaware V1.005 ===");

    persistence_init();

    display_init();
    //test de eeprom to cache
    const MachineConfig *cfg = machine_config_get();
    Console_Print(MSG_DBG,"Custom [0]: %s led: %ld", cfg->customer[0], cfg->Led1_time);
    menu_init();
    encoder_init();
//---------------------------------------




//---------------------------------------

    

    machine_init();
    system_init();
    
    // motorSystem_init();
}