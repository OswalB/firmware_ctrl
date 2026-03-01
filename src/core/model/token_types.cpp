#include "token_types.h"

TokenClass get_token_class(Token *t)
{
    switch (t->type)
    {
        case TOKEN_CMD:    return TK_CMD;
        case TOKEN_DOMAIN: return TK_DOMAIN;
        case TOKEN_NUMBER: return TK_NUMBER;
        case TOKEN_PARAM:  return TK_PARAM;
        default:           return TK_INVALID;
    }
}