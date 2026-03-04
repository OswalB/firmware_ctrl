#include "parser.h"
#include "modules/console/console.h"
#include "lib/utils/utils.h"
#include "core/event/event_queue.h"
#include "core/fsm/machine.h"
#include "core/model/token_types.h"
#include "clasifer.h"
#include "input/command/evaluator.h"
#include "core/model/semantic_validator.h"

#define MAX_TOKEN_LENGTH 32
#define MAX_TOKENS 8

static int tokenize(const char *line, char tokens[][MAX_TOKEN_LENGTH]);

// --------------------------------------------
// Parser text (cli)
// --------------------------------------------
    void parser_parse_line(const char *line)
{
    char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
    int token_count = tokenize(line, tokens);

    if (token_count == 0)
        return;

    // Normalización
    for (int i = 0; i < token_count; i++)
    {
        if (!utils_is_numeric(tokens[i]))
            utils_to_uppercase(tokens[i]);
    }

    // --- LEXER
    Token typed[MAX_TOKENS];
    uint8_t cntErrors = classify_tokens(tokens, token_count, typed);

    if (cntErrors > 0)
    {
        Console_Print(MSG_ERR, "%d format errors", cntErrors);
        return;
    }

    Console_Print(MSG_LOG, "Lexer OK");

    // --- MOTOR tk
    parser_process_tokens(typed, token_count);
}

// --------------------------------------------
// Parser tokens (core)
// --------------------------------------------

bool parser_process_tokens(Token *typed, int token_count)
{
    Event evt;

    // --- SINTAXIS
    if (!evaluate_command(typed, token_count, &evt))
    {
        Console_Print(MSG_ERR, "Syntax error");
        return false;
    }

    Console_Print(MSG_LOG, "Event built");

    // --- SEMÁNTICA
    Response response = validate_semantics(&evt);
    if (response.type != RESP_OK)
    {
        Console_Print(MSG_ERR, "E %s", response.text);
        return false;
    }
    Console_Print(MSG_LOG, "Semantics ok");
    // --- DISPATCH
    eventQueue_push(evt);

    Console_Print(MSG_LOG,
                  "OK evt pushed event=%s dom=%d id=%d param=%d value=%ld",
                  enum_toString(evt.type, EventType_str, EVT_COUNT),
                  evt.domain,
                  evt.id,
                  evt.param,
                  evt.value);

    return true;
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