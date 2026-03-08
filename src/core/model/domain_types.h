#pragma once
#include <stdint.h>

typedef enum
{
    DOMAIN_UNKNOW = 0,
    DOMAIN_MOTOR,
    DOMAIN_LED,
    DOMAIN_SENSOR,
    DOMAIN_CUSTOM,
    DOMAIN_COUNT
} DomainType;