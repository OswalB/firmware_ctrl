#include "BORRARsemantic_validator.h"

bool BORRARvalidate_semantics(Event *ev)
{
    switch (ev->domain)
    {
        case DOMAIN_LED:

            if (ev->param != PARAM_STATE)
                return false;

            break;

        case DOMAIN_MOTOR:

            if (ev->param != PARAM_SPEED)
                return false;

            break;

        case DOMAIN_SENSOR:

            // Por ejemplo solo GET
            if (ev->type != EVT_GET)
                return false;

            break;

        default:
            return false;
    }

    return true;
}