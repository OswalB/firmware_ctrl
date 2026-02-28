#include <stddef.h>
#include "err_types.h"

typedef struct
{
    ErrorType type;
    const char* text;
} ErrorMap;

static const ErrorMap error_map[] =
{
    { ERR_UNKNOW,        "Unknown error" },
    { ERR_NONE,          "No error" },
    { ERR_COM,           "Command error" },
    { ERR_DOMANIN,       "Domain error" },
    { ERR_ID_DOMAIN,     "Invalid domain ID" },
    { ERR_PARAM,         "Parameter error" },
    { ERR_VALUE_PARAM,   "Invalid parameter value" },
    { ERR_RANGE_PARAM,   "Parameter out of range" },
    { ERR_EVENT_UNKNOW,  "Unknown event" }
};

const char* ErrorType_toString(ErrorType err)
{
    for (size_t i = 0; i < sizeof(error_map)/sizeof(error_map[0]); ++i)
    {
        if (error_map[i].type == err)
            return error_map[i].text;
    }

    return "Invalid error code";
}