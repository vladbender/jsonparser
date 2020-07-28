#pragma once

#include <string>

#include "../types/Types.h"

namespace JSON {
	AbstractObject* parse(const std::string& json);
	String* parseString(const std::string& json);
	Number* parseNumber(const std::string& json);
	Boolean* parseBoolean(const std::string& json);
	Array* parseArray(const std::string& json);
	Object* parseObject(const std::string& json);
}
