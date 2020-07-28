
#include <sstream>

#include "Number.h"

namespace JSON {
	std::string Number::toString() const {
		std::ostringstream strs;
		strs << value;
		return strs.str();
	}
}
