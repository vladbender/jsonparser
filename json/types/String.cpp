
#include "String.h"
#include "../utils/Utils.h"

namespace JSON {
	std::string String::toString() const {
		return "\"" + escapeQuotes(value) + "\"";
	}
}
