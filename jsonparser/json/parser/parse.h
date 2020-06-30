#pragma once

#include <string>

#include "../types/AbstractObject.h"

namespace JSON {
	AbstractObject* parse(std::string json);
}
