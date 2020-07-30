#pragma once

#include <vector>
#include <string>

#include "AbstractObject.h"
#include "Boolean.h"
#include "Number.h"
#include "String.h"
#include "Object.h"

namespace JSON {
	class Object;
	class Array : public AbstractObject {
	public:
		Array() : AbstractObject() {
			type = Type::ARRAY;
		}
		~Array();
		AbstractObject* operator[](size_t pos);
		AbstractObject* at(size_t pos) {
			return (*this)[pos];
		}
		void push(AbstractObject* obj) {
			values.push_back(obj);
		}
		std::string toString() const;
		size_t size() const {
			return this->values.size();
		}
		Boolean* booleanAt(size_t pos);
		Number* numberAt(size_t pos);
		Object* objectAt(size_t pos);
		String* stringAt(size_t pos);
		Array* arrayAt(size_t pos);
	private:
		// Может хранить ссылки?
		std::vector<AbstractObject*> values;
	};
}