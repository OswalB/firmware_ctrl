#include "event_types.h"

const char* const EventType_str[EVT_COUNT] =
{
    "EVT_UNKNOW",
    //Eventos externos
    "EVT_SET",
    "EVT_GET",
    "EVT_START",
    "EVT_STOP",
    "EVT_ERROR",
    "EVT_RESET",
    //Eventos de error
    "EV_PARSE_UNKNOWN",
    "EV_PARSE_INVALID_PARAM",
    // Eventos internos (desde fsm_update)
    "EV_TIMEOUT",
    "EV_HW_FAULT",
    "EV_OPERATION_DONE",
    "EV_TYPE_REQUEST"

};