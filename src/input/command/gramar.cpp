#include <stdlib.h>

#include "gramar.h"

static const GrammarRule grammar[] =
{
    {1, {TK_CMD}},
    {3, {TK_CMD, TK_DOMAIN, TK_VALUE}},                // ID
    {4, {TK_CMD, TK_DOMAIN, TK_VALUE, TK_VALUE}},     // valor implícito
    {5, {TK_CMD, TK_DOMAIN, TK_VALUE, TK_PARAM, TK_VALUE}}
};

#define GRAMMAR_COUNT (sizeof(grammar)/sizeof(grammar[0]))

bool match_grammar(TokenClass types[], uint8_t count)
{
    for (size_t i = 0; i < GRAMMAR_COUNT; i++)
    {
        if (grammar[i].length != count)
            continue;

        bool match = true;

        for (int j = 0; j < count; j++)
        {
            if (grammar[i].pattern[j] != types[j])
            {
                match = false;
                break;
            }
        }

        if (match)
            return true;
    }

    return false;
}