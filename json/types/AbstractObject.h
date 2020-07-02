#pragma once

#include <string>

#include "../Type.h"

namespace JSON {
	class AbstractObject {
	public:
		AbstractObject() {
			type = Type::NONE;
		}

		Type getType() {
			return type;
		}

		virtual std::string toString() = 0;

	protected:
		Type type;
	};
}