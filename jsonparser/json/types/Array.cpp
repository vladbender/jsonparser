
#include "Array.h"

namespace JSON {
	Array::~Array() {
		for (size_t i = 0; i < values.size(); i++) {
			delete values[i];
		}
	}

	AbstractObject* Array::operator[](size_t pos) {
		// "at" checks out of range
		return values.at(pos);
	}

	std::string Array::toString() {
		std::string result = "[";

		for (size_t i = 0; i < values.size(); i++) {
			result += " " + values[i]->toString();

			if (i != values.size() - 1) {
				result += ",";
			} else {
				result += " ";
			}
		}

		result += "]";
		return result;
	}
}
