#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "evaluator.h"
#include "core/types/event_types.h"
#include "core/types/token_types.h"
#include "input/command/clasifer.h"
#include "input/command/dictionary.h"
#include "input/command/gramar.h"



bool evaluate_command(Token *tokens, int token_count, Event *out)
{
    if (token_count < 1)
        return false;

    memset(out, 0, sizeof(Event));

    // El primer token siempre debe ser CMD
    if (tokens[0].type != TOKEN_CMD)
        return false;

    out->type = tokens[0].cmd;

    switch (token_count)
    {
        case 1:
            return true;

        case 3:
            if (tokens[1].type != TOKEN_DOMAIN ||
                tokens[2].type != TOKEN_NUMBER)
                return false;

            out->domain = tokens[1].domain;
            out->id     = tokens[2].number;
            return true;

        case 4:
            if (tokens[1].type != TOKEN_DOMAIN ||
                tokens[2].type != TOKEN_NUMBER ||
                tokens[3].type != TOKEN_NUMBER)
                return false;

            out->domain = tokens[1].domain;
            out->id     = tokens[2].number;
            out->value  = tokens[3].number;
            return true;

        case 5:
            if (tokens[1].type != TOKEN_DOMAIN ||
                tokens[2].type != TOKEN_NUMBER ||
                tokens[3].type != TOKEN_PARAM  ||
                tokens[4].type != TOKEN_NUMBER)
                return false;

            out->domain = tokens[1].domain;
            out->id     = tokens[2].number;
            out->param  = tokens[3].param;
            out->value  = tokens[4].number;
            return true;

        default:
            return false;
    }
}