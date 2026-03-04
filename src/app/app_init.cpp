// #include "core/event/event_queue.h"
#include "modules/led/led_module.h"
#include "input/serial/serial_if.h"
#include "core/fsm/machine.h"
// #include "modules/motor/motor.h"
#include "modules/console/console.h"
#include "modules/system/system.h"
#include "../modules/persist/persist.h"

void app_init()
{
    persist_init();


    
    // eventQueue_init();
    led::led_init();

    Console_SetMode(CONSOLE_ALL);
    serial_init();
    serial_writeln("=== Firmaware V1.004 ===");

    machine_init();
    system_init();
    Console_Print(MSG_LOG, "EEPROM Slot size: %u", persist_get_slot_size());
    Console_Print(MSG_LOG, "Config size: %u", persist_get_config_size());
    Console_Print(MSG_LOG, "Remaining: %u", persist_get_remaining_bytes());
    // motorSystem_init();
}