#pragma once
#include <stdbool.h>
#include "core/command/command_resolver.h"
#include "core/types/event_types.h"

bool event_build_from_match(
    const CommandMatch *match,
    Event *out_event);