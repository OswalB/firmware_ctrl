#pragma once

typedef enum
{
    RESP_ERROR = 0,
    RESP_OK,
    RESP_FAULT,
    RESP_INFO,
    RESP_ERR_UNKNOW,
    RESP_ERR_COMMAND,
    RESP_ERR_EVENT,
    ERR_COUNT

} ResponseType;

typedef struct
{
    ResponseType type;
    const char *text;
} Response;

const char *responseType_toString(ResponseType err);