#pragma once

#include <string>
#include "TokenType.h"

struct Token {
	TokenType type;
	std::string rawValue;
};
