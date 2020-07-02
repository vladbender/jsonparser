#pragma once

#include <string>

#include "AbstractObject.h"

namespace JSON {
	class Null : public AbstractObject {
	public:
		Null() : AbstractObject() {
			type = Type::NULL_;
		}

		std::string toString() {
			return "null";
		}
	};
}