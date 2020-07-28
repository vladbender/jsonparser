#pragma once

#include <string>

#include "../Type.h"

namespace JSON {
	class AbstractObject {
	public:
		AbstractObject() {
			type = Type::NONE;
		}

		Type getType() const {
			return type;
		}

		virtual std::string toString() const = 0;

	protected:
		Type type;
	};
}