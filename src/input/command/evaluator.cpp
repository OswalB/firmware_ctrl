#include <stdint.h>
#include <stdlib.h>
#include "evaluator.h"
#include "core/types/event_types.h"
#include "core/types/token_types.h"
#include "input/command/clasifer.h"
#include "input/command/dictionary.h"
#include "input/command/gramar.h"

bool evaluate_command(char* tokens[],
                      uint8_t token_count,
                      Event* out)
{
    TokenClass types[5];

    // Clasificar tokens
    for (int i = 0; i < token_count; i++)
        //types[i] = classify_tokens(tokens[i]);      ATENCION!!!!!

    // Ajustar ID vs VALUE
    if (token_count >= 3 && types[2] == TK_VALUE)
        types[2] = TK_VALUE;  // será ID en construcción

    if (!match_grammar(types, token_count))
        return false;

    // Construir evento
    out->type = EV_TYPE_REQUEST;
    out->command = cmd_from_string(tokens[0]);

    if (token_count >= 3)
    {
        out->domain = domain_from_string(tokens[1]);
        out->id     = atoi(tokens[2]);
    }

    if (token_count == 4)
    {
        out->param = PARAM_UNKNOWN;
        out->value = atoi(tokens[3]);
    }

    if (token_count == 5)
    {
        out->param = param_from_string(tokens[3]);
        out->value = atoi(tokens[4]);
    }

    return true;
}