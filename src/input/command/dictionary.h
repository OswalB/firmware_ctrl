#pragma once

#include "core/types/command_types.h"
#include "core/types/domain_types.h"
#include "core/types/param_types.h"

CommandType cmd_from_string(const char* str);
DomainType domain_from_string(const char* str);
ParamType param_from_string(const char* str);

