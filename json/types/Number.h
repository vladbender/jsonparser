#pragma once

#include <string>

#include "AbstractObject.h"

namespace JSON {
	class Number : public AbstractObject {
	public:
		Number(double v) : AbstractObject(), value(v) {
			type = Type::NUMBER;
		}

		double getValue() const {
			return value;
		}

		std::string toString() const;

	private:
		double value;
	};
}