#include <ctype.h>
#include <stdbool.h>

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

/*==================================================
                 CONVERT
====================================================*/
