#pragma once

#include "fromTypeToString.h"
#include "../exceptions/ExpectedException.h"
#include "../Type.h"

void expectType(const JSON::Type& expected, const JSON::Type& received);