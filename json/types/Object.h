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

		AbstractObject* operator[](const std::string&);

		void set(const std::string&, AbstractObject*);

		std::string toString();

	private:
		std::unordered_map<std::string, AbstractObject*> values;
	};
}