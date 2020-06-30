#pragma once

#include <string>

#include "AbstractObject.h"

namespace JSON {
	class Number : public AbstractObject {
	public:
		Number(double v) : AbstractObject(), value(v) {
			type = Type::NUMBER;
		}

		double getValue() {
			return value;
		}

		std::string toString();

	private:
		double value;
	};
}