#pragma once
#include "core/types/event_types.h"

typedef enum
{
    MS_IDLE = 0,
    MS_RUNNING,
    MS_ERROR,
    MS_BUSY
} MachineState;

typedef enum {
    RESP_OK,
    RESP_ERROR,
    RESP_FAULT,
    RESP_INFO
} ResponseType;

typedef struct {
    ResponseType type;
    const char* text;
} Response;

bool fsm_hasOutput(void);
Response fsm_getOutput(void);

void machine_init(void);
void machine_update(void);
void fsm_dispatchEvent(EventType ev);
void fsm_push(ResponseType type, const char* text);

void fsm_handleCommand(const char* cmd);


MachineState fsm_getState(void);