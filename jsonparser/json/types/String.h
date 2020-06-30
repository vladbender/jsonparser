#pragma once

#include <string>

#include "AbstractObject.h"

namespace JSON {
	class String : public AbstractObject {
	public:
		String(std::string s) : AbstractObject(), value(s) {
			type = Type::STRING;
		}

		std::string getValue() {
			return value;
		}

		std::string toString();

	private:
		std::string value;
	};
}