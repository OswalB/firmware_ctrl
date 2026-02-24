#include <stdint.h>
#include "core/fsm/machine.h"
#include <string.h>
//#include "core/event/event_queue.h"
//#include "core/types/event_types.h"
//#include "modules/led/led.h"
//#include "drivers/led_pwm/led_pwm.h"

static void fsm_push(ResponseType type, const char* text);

static MachineState fsm_state = MS_IDLE;
static MachineState g_state;

#define FSM_QUEUE_SIZE 8

static Response responseQueue[FSM_QUEUE_SIZE];
static uint8_t queueHead = 0;
static uint8_t queueTail = 0;

void machine_init(void)
{
    g_state = MS_IDLE;
    //led_run_set(RUN_LED_IDLE);
    queueHead = 0;
    queueTail = 0;
    fsm_state = MS_IDLE;
}









// Handler


void fsm_handleCommand(const char* cmd)
{
    if (fsm_state == MS_ERROR)
    {
        fsm_push(RESP_FAULT, "system in fault state");
        return;
    }

    if (strcmp(cmd, "start") == 0)
    {
        fsm_state = MS_BUSY;
        fsm_push(RESP_INFO, "processing...");
    }
    else if (strcmp(cmd, "ok") == 0)
    {
        fsm_state = MS_IDLE;
        fsm_push(RESP_OK, "");
    }
    else if (strcmp(cmd, "fail") == 0)
    {
        fsm_state = MS_IDLE;
        fsm_push(RESP_ERROR, "operation failed");
    }
    else if (strcmp(cmd, "timeout") == 0)
    {
        fsm_state = MS_ERROR;
        fsm_push(RESP_FAULT, "timeout");
    }
    else
    {
        fsm_push(RESP_ERROR, "unknown command");
    }
}

static void fsm_push(ResponseType type, const char* text)
{
    uint8_t next = (queueHead + 1) % FSM_QUEUE_SIZE;

    if (next != queueTail)   // evita overflow
    {
        responseQueue[queueHead].type = type;
        responseQueue[queueHead].text = text;
        queueHead = next;
    }
}

bool fsm_hasOutput(void)
{
    return (queueHead != queueTail);
}

Response fsm_getOutput(void)
{
    Response r = responseQueue[queueTail];
    queueTail = (queueTail + 1) % FSM_QUEUE_SIZE;
    return r;
}

MachineState fsm_getState(void)
{
    return fsm_state;
}