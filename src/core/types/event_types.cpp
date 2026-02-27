#include "event_types.h"

const char* const EventType_str[EVT_COUNT] =
{
    //Eventos externos
    "EVT_NONE",
    "EVT_SET",
    "EVT_GET",
    "EVT_START",
    "EVT_STOP",
    "EVT_ERROR",
    "EVT_RESET",
    "EVT_MODE_SET",
    "EVT_SET_SPEED",
    //Eventos de error
    "EV_PARSE_UNKNOWN",
    "EV_PARSE_INVALID_PARAM",
    // Eventos internos (desde fsm_update)
    "EV_TIMEOUT",
    "EV_HW_FAULT",
    "EV_OPERATION_DONE",
    "EV_TYPE_REQUEST"

};