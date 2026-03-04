#include <stddef.h>
#include "response_types.h"

typedef struct
{
    ResponseType type;
    const char *text;
} ResponseMap;

static const ResponseMap resp_map[] =
    {
        {RESP_ERR_UNKNOW, "Unknown error"},
        {RESP_OK, "OK"},
        {RESP_ERR_COMMAND, "Command error rsp"},
        {RESP_FAULT, "Fault"},
        {RESP_INFO, "Info"},
        {RESP_ERROR, "Error"},
        {RESP_ERR_EVENT, "Event error"}

};

const char *responseType_toString(ResponseType err)
{
    for (size_t i = 0; i < sizeof(resp_map) / sizeof(resp_map[0]); ++i)
    {
        if (resp_map[i].type == err)
            return resp_map[i].text;
    }

    return "Invalid response code";
}