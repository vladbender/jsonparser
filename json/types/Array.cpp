
#include "Array.h"
#include "../utils/Utils.h"

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

	std::string Array::toString() const {
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

	Boolean* Array::booleanAt(size_t pos) {
		auto value = (*this)[pos];
		expectType(value->getType(), Type::BOOLEAN);
		return (Boolean*)value;
	}

	Number* Array::numberAt(size_t pos) {
		auto value = (*this)[pos];
		expectType(value->getType(), Type::NUMBER);
		return (Number*)value;
	}

	Object* Array::objectAt(size_t pos) {
		auto value = (*this)[pos];
		expectType(value->getType(), Type::OBJECT);
		return (Object*)value;
	}

	String* Array::stringAt(size_t pos) {
		auto value = (*this)[pos];
		expectType(value->getType(), Type::STRING);
		return (String*)value;
	}

	Array* Array::arrayAt(size_t pos) {
		auto value = (*this)[pos];
		expectType(value->getType(), Type::ARRAY);
		return (Array*)value;
	}
}
