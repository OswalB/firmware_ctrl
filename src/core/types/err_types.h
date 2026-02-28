#pragma once

typedef enum
{
    ERR_UNKNOW =0,
    ERR_NONE,
    //dE CONSOLA
    ERR_COM,
    ERR_DOMANIN,
    ERR_ID_DOMAIN,
    ERR_PARAM,
    ERR_VALUE_PARAM,
    ERR_RANGE_PARAM,
    ERR_EVENT_UNKNOW,
    ERR_COUNT

}ErrorType;

const char* ErrorType_toString(ErrorType err);