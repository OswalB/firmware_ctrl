#include "event_queue.h"

static EventQueue g_queue;

void eventQueue_init(void)
{
    g_queue.head = 0;
    g_queue.tail = 0;
    g_queue.count = 0;
}

bool eventQueue_isEmpty(void)
{
    return (g_queue.count == 0);
}

bool eventQueue_push(Event evt)
{
    if (g_queue.count >= EVENT_QUEUE_SIZE)
    {
        return false; // Cola llena
    }

    g_queue.buffer[g_queue.head] = evt;
    g_queue.head = (g_queue.head + 1) % EVENT_QUEUE_SIZE;
    g_queue.count++;

    return true;
}

bool eventQueue_pop(Event *evt)
{
    if (g_queue.count == 0)
    {
        return false;
    }

    *evt = g_queue.buffer[g_queue.tail];
    g_queue.tail = (g_queue.tail + 1) % EVENT_QUEUE_SIZE;
    g_queue.count--;

    return true;
}
