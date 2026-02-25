#include "parser.h"
#include "system/console/console.h"
#include "lib/utils/utils.h"
#include "core/command/command_resolver.h"
#include "core/event/event_builder.h"
#include "core/event/event_queue.h"
#include "core/fsm/machine.h"

#define MAX_TOKEN_LENGTH 32
#define MAX_TOKENS 8

static int tokenize(const char *line, char tokens[][MAX_TOKEN_LENGTH]);

// --------------------------------------------
// Parser principal
// --------------------------------------------
void parser_parse(const char *line)
{
    fsm_push(RESP_ERROR,"test1");
    fsm_push(RESP_FAULT,"test6");
    char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
    int token_count = tokenize(line, tokens);

    if (token_count == 0)
        return;

    for (int i = 0; i < token_count; i++)
    {
        if (!utils_is_numeric(tokens[i]))
        {
            utils_to_uppercase(tokens[i]);
        }
    }

    CommandMatch match;

    if (!command_resolve(tokens, token_count, &match))
    {
        Console_Print(MSG_LOG, "log> ERR: Unknown command\n");
        fsm_dispatchEvent(EV_PARSE_UNKNOWN);
        return;
    }

    Console_Print(MSG_LOG, "log> ok resolve %s", tokens[0]);

    Event event;

    if (!event_build_from_match(&match, &event))
    {
        Console_Print(MSG_LOG,"log> ERR: Cannot build event\n");
        return;
    }

    eventQueue_push(event);

    Console_Print(MSG_LOG, "log> ok evt pushed cmd=%s dom=%d id=%d param=%d value=%ld",
                  enum_toString(event.type, EventType_str, EVT_COUNT),
                  event.domain,
                  event.id,
                  event.param,
                  event.value);
}

// --------------------------------------------
// Tokenizador simple
// --------------------------------------------
static int tokenize(const char *line, char tokens[][MAX_TOKEN_LENGTH])
{
    int count = 0;

    const char *ptr = line;

    while (*ptr != '\0' && count < MAX_TOKENS)
    {
        while (*ptr == ' ')
            ptr++;

        if (*ptr == '\0')
            break;

        int len = 0;
        while (*ptr != ' ' && *ptr != '\0' && len < MAX_TOKEN_LENGTH - 1)
        {
            tokens[count][len++] = *ptr++;
        }

        tokens[count][len] = '\0';
        count++;
    }

    return count;
}