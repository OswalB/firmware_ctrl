#include "command_resolver.h"
#include <string.h>
#include <stdlib.h>
#include "core/types/domain_types.h"
#include "core/types/event_types.h"
#include "core/types/param_types.h"

bool command_resolve(
    char tokens[][32],
    int token_count,
    CommandMatch *out_match)
{
    if (token_count < 5)
        return false;

    memset(out_match, 0, sizeof(CommandMatch));

    // COMMAND
    if (strcmp(tokens[0], "SET") == 0)
        out_match->type = EVT_SET;
    else if (strcmp(tokens[0], "GET") == 0)
        out_match->type = EVT_GET;
    else
        return false;

    // DOMAIN
    if (strcmp(tokens[1], "MOTOR") == 0)
        out_match->domain = DOMAIN_MOTOR;
    else if (strcmp(tokens[1], "SENSOR") == 0)
        out_match->domain = DOMAIN_SENSOR;
    else if (strcmp(tokens[1], "LED") == 0)
        out_match->domain = DOMAIN_LED;
    else
        return false;

    // ID
    out_match->id = (uint8_t)atoi(tokens[2]);

    // PARAM
    if (strcmp(tokens[3], "SPEED") == 0)
        out_match->param = PARAM_SPEED;
    else if (strcmp(tokens[3], "POSITION") == 0)
        out_match->param = PARAM_POSITION;
    else if (strcmp(tokens[3], "STATE") == 0)
        out_match->param = PARAM_STATE;
    else
        return false;

    // VALUE
    out_match->value = atoi(tokens[4]);

    return true;
}
