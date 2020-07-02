#pragma once

#include <string>
#include <unordered_map>

#include "AbstractObject.h"

namespace JSON {
	class Object : public AbstractObject {
	public:
		Object() : AbstractObject() {
			type = Type::OBJECT;
		}

		~Object();

		AbstractObject* operator[](std::string);

		void set(std::string key, AbstractObject* obj);

		std::string toString();

	private:
		std::unordered_map<std::string, AbstractObject*> values;
	};
}