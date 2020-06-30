#pragma once

#include <string>

#include "AbstractObject.h"

namespace JSON {
	class Boolean : public AbstractObject {
	public:
		Boolean(bool b) : AbstractObject(), value(b) {
			type = Type::BOOLEAN;
		}

		bool getValue() {
			return value;
		}

		std::string toString() {
			return value ? "true" : "false";
		}

	private:
		bool value;
	};
}