
#include "String.h"
#include "../utils/Utils.h"

namespace JSON {
	std::string String::toString() {
		return "\"" + escapeQuotes(value) + "\"";
	}
}
