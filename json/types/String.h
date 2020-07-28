#pragma once

#include <string>

#include "AbstractObject.h"

namespace JSON {
	class String : public AbstractObject {
	public:
		String(std::string s) : AbstractObject(), value(s) {
			type = Type::STRING;
		}

		std::string getValue() const{
			return value;
		}

		std::string toString() const;

	private:
		std::string value;
	};
}