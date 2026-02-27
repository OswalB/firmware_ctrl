#include <string.h>
#include "dictionary.h"

// Tabla Command
typedef struct
{
    const char*  name;
    CommandType  type;
} CmdEntry;

static const CmdEntry cmd_table[] =
{
    {"SET",    CMD_SET},
    {"GET",    CMD_GET},
    {"STATUS", CMD_STATUS},
    {"RESET",  CMD_RESET}
};

#define CMD_COUNT (sizeof(cmd_table)/sizeof(cmd_table[0]))

CommandType cmd_from_string(const char* str)
{
    for (size_t i = 0; i < CMD_COUNT; i++)
    {
        if (strcmp(str, cmd_table[i].name) == 0)
            return cmd_table[i].type;
    }

    return CMD_UNKNOWN;
}

// Tabla Domain
typedef struct
{
    const char* name;
    DomainType  type;
} DomainEntry;

static const DomainEntry domain_table[] =
{
    {"LED",    DOMAIN_LED},
    {"MOTOR",  DOMAIN_MOTOR},
    {"SENSOR", DOMAIN_SENSOR}
};

#define DOMAIN_COUNT (sizeof(domain_table)/sizeof(domain_table[0]))

DomainType domain_from_string(const char* str)
{
    for (size_t i = 0; i < DOMAIN_COUNT; i++)
    {
        if (strcmp(str, domain_table[i].name) == 0)
            return domain_table[i].type;
    }

    //return DOMAIN_NONE;
}

// Tabla Param

typedef struct
{
    const char* name;
    ParamType   type;
} ParamEntry;

static const ParamEntry param_table[] =
{
    {"STATE",     PARAM_STATE},
    {"DUTY",      PARAM_DUTY},
    {"SPEED",     PARAM_SPEED},
    {"THRESHOLD", PARAM_THRESHOLD}
};

#define PARAM_COUNT (sizeof(param_table)/sizeof(param_table[0]))

ParamType param_from_string(const char* str)
{
    for (size_t i = 0; i < PARAM_COUNT; i++)
    {
        if (strcmp(str, param_table[i].name) == 0)
            return param_table[i].type;
    }

    return PARAM_NONE;
}