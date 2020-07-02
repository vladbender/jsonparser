#pragma once

#include <vector>
#include <string>

#include "AbstractObject.h"

namespace JSON {
	class Array : public AbstractObject {
	public:
		Array() : AbstractObject() {
			type = Type::ARRAY;
		}

		~Array();

		AbstractObject* operator[](size_t pos);

		void push(AbstractObject* obj) {
			values.push_back(obj);
		}

		std::string toString();

	private:
		// Может хранить ссылки?
		std::vector<AbstractObject*> values;
	};
}