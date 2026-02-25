#include "event_builder.h"
#include <string.h>

bool event_build_from_match(
    const CommandMatch *match,
    Event *out_event)
{
    if (!match || !out_event)
        return false;

    *out_event = *(Event *)match;
    return true;
}