#include <ctype.h>
#include <stdbool.h>
#include <Arduino.h>

/*==================================================
                 STRINGS
====================================================*/

bool utils_is_numeric(const char *str)
{
    if (*str == '-' || *str == '+')
        str++;

    if (*str == '\0')
        return false;

    while (*str)
    {
        if (!isdigit((unsigned char)*str))
            return false;
        str++;
    }

    return true;
}

void utils_to_uppercase(char *str)
{
    while (*str)
    {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

//utils_strcopy_safe(cfg->customer[0], "Abc", sizeof(cfg->customer[0]));
void utils_strcopy_safe(char *dst, const char *src, size_t size)
{
    if (size == 0) return;

    size_t i;

    for (i = 0; i < size - 1 && src[i] != '\0'; i++)
        dst[i] = src[i];

    dst[i] = '\0';
}

/*==================================================
                 CONVERT
====================================================*/

const char* enum_toString(int value,
                          const char* const table[],
                          int count)
{
    if (value >= 0 && value < count)
        return table[value];

    return "UNKNOWN";
}