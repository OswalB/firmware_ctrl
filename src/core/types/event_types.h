#pragma once
#include <stdint.h>
#include "core/types/domain_types.h"
#include "core/types/param_types.h"

typedef enum
{
    //Eventos externos
    EVT_NONE = 0,
    EVT_SET,
    EVT_GET,
    EVT_SET_LED_DUTY,
    EVT_SET_LED_TIME,
    EVT_START,
    EVT_STOP,
    EVT_ERROR,
    EVT_RESET,
    EVT_MODE_SET,
    EVT_SET_SPEED,
    //Eventos de error
    EV_PARSE_UNKNOWN,
    EV_PARSE_INVALID_PARAM,
    // Eventos internos (desde fsm_update)
    EV_TIMEOUT,
    EV_HW_FAULT,
    EV_OPERATION_DONE,

    EVT_COUNT

} EventType;

extern const char* const EventType_str[EVT_COUNT];


typedef struct
{
    EventType type;    // Qué ocurrió
    DomainType domain; // MOTOR, LED, SENSOR
    uint8_t id;        // Instancia Quién lo generó / a quién aplica
    ParamType param;   // SPEED, POSITION, ...
    int32_t value;     // Dato asociado
} Event;
