#include "drivers/eeprom/eeprom_driver.h"
#include "modules/console/console.h"
#include "persistence .h"



//-----------------------------------------
//---- FORWARDS
//-----------------------------------------




void persistence_init()
{
    Console_Print(MSG_DBG,"EEPROM init:");
    


}


//-----------------------------------------
//---- TESTS VERIFY
//-----------------------------------------


{
    uint32_t expected = 0x12345678;
    uint32_t value = 0;

    eeprom_read_bytes(0, (uint8_t*)&value, sizeof(value));
    Console_Print(MSG_DBG,"EEPROM value: 0x%08lX", value);


    if(value == expected)
    {
        Console_Print(MSG_LOG,"EEPROM retained value OK");
    }
    else if(value == 0xFFFFFFFF || value == 0x00000000)
    {
        Console_Print(MSG_LOG,"EEPROM empty, writing test value");

        eeprom_write_bytes(0, (uint8_t*)&expected, sizeof(expected));
    }
    else
    {
        Console_Print(MSG_ERR,"EEPROM unexpected value");
    }
}