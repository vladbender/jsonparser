#pragma once

#include <string>

#include "AbstractObject.h"

namespace JSON {
	class Boolean : public AbstractObject {
	public:
		Boolean(bool b) : AbstractObject(), value(b) {
			type = Type::BOOLEAN;
		}

		bool getValue() const {
			return value;
		}

		std::string toString() const {
			return value ? "true" : "false";
		}

	private:
		bool value;
	};
}