
#include <sstream>

#include "Number.h"

namespace JSON {
	std::string Number::toString() {
		std::ostringstream strs;
		strs << value;
		return strs.str();
	}
}
