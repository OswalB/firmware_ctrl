#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "lib/utils/utils.h"
#include "clasifer.h"
#include "core/model/token_types.h"
#include "core/model/domain_types.h"
#include "core/model/param_types.h"
#include "core/model/command_types.h"
#include "lib/utils/utils.h"



uint8_t classify_tokens(
    char raw_tokens[][32],
    int token_count,
    Token *out_tokens)
{
    uint8_t errCount = 0;
    for (int i = 0; i < token_count; i++)
    {
        char *word = raw_tokens[i];

        // COMMAND
        if (strcmp(word, "SET") == 0)
        {
            out_tokens[i].type = TOKEN_CMD;
            out_tokens[i].cmd = EVT_SET;
        }
        else if (strcmp(word, "GET") == 0)
        {
            out_tokens[i].type = TOKEN_CMD;
            out_tokens[i].cmd = EVT_GET;
        }

        // DOMAIN
        else if (strcmp(word, "LED") == 0)
        {
            out_tokens[i].type = TOKEN_DOMAIN;
            out_tokens[i].domain = DOMAIN_LED;
        }
        else if (strcmp(word, "MOTOR") == 0)
        {
            out_tokens[i].type = TOKEN_DOMAIN;
            out_tokens[i].domain = DOMAIN_MOTOR;
        }
        else if (strcmp(word, "SENSOR") == 0)
        {
            out_tokens[i].type = TOKEN_DOMAIN;
            out_tokens[i].domain = DOMAIN_SENSOR;
        }

        // PARAM
        else if (strcmp(word, "STATE") == 0)
        {
            out_tokens[i].type = TOKEN_PARAM;
            out_tokens[i].param = PARAM_STATE;
        }
        else if (strcmp(word, "SPEED") == 0)
        {
            out_tokens[i].type = TOKEN_PARAM;
            out_tokens[i].param = PARAM_SPEED;
        }
        else if (strcmp(word, "DUTY") == 0)
        {
            out_tokens[i].type = TOKEN_PARAM;
            out_tokens[i].param = PARAM_DUTY;
        }

        // NUMBER
        else if (utils_is_numeric(word))
        {
            out_tokens[i].type = TOKEN_NUMBER;
            out_tokens[i].number = atoi(word);
        }

        // UNKNOWN
        else
        {
            out_tokens[i].type = TOKEN_UNKNOWN;
            errCount++;
        }
    }

    return errCount;
}