
#include "Object.h"
#include "../utils/Utils.h"

namespace JSON {
	Object::~Object() {
		for (auto it = values.begin(); it != values.end(); it++) {
			delete it->second;
		}
	}

	void Object::set(const std::string& key, AbstractObject* obj) {
		auto has = values.find(key);
		if (has == values.end()) {
			// Нет другого элемента с таким ключом - добавляем
			values[key] = obj;
		} else if (has->second != obj) {
			// Такой элемент существует,
			// но при этом не является указателем на тот же объект
			delete has->second;
			values[key] = obj;
		}
	}

	AbstractObject* Object::operator[](const std::string& key) {
		auto has = values.find(key);
		if (has == values.end()) {
			return nullptr;
		} else {
			return has->second;
		}
	}

	std::string Object::toString() const {
		std::string result = "{";
		int i = 0;
		int last = values.size() - 1;
		for (auto it = values.begin(); it != values.end(); it++, i++) {
			result += " \"" + escapeQuotes(it->first) + "\": " + it->second->toString();
			if (i != last) {
				result += ",";
			} else {
				result += " ";
			}
		}
		result += "}";
		return result;
	}

	Number* Object::getNumber(const std::string& key) {
		auto value = (*this)[key];
		if (value == nullptr) return nullptr;
		expectType(value->getType(), Type::NUMBER);
		return (Number*)value;
	};

	String* Object::getString(const std::string& key) {
		auto value = (*this)[key];
		if (value == nullptr) return nullptr;
		expectType(value->getType(), Type::STRING);
		return (String*)value;
	};

	Boolean* Object::getBoolean(const std::string& key) {
		auto value = (*this)[key];
		if (value == nullptr) return nullptr;
		expectType(value->getType(), Type::BOOLEAN);
		return (Boolean*)value;
	};

	Array* Object::getArray(const std::string& key) {
		auto value = (*this)[key];
		if (value == nullptr) return nullptr;
		expectType(value->getType(), Type::ARRAY);
		return (Array*)value;
	};

	Object* Object::getObject(const std::string& key) {
		auto value = (*this)[key];
		if (value == nullptr) return nullptr;
		expectType(value->getType(), Type::OBJECT);
		return (Object*)value;
	};

	Object::iterator::iterator(
		const std::unordered_map<std::string, AbstractObject*>& values,
		bool isBegin
	) {
		if (isBegin) {
			it = values.begin();
		} else {
			it = values.end();
		}
	}

	Object::iterator Object::iterator::operator++() {
		Object::iterator old = *this;
		++it;
		return old;
	}

	Object::iterator Object::iterator::operator++(int val) {
		it++;
		return *this;
	}

	std::pair<std::string, AbstractObject*> Object::iterator::operator*() {
		return *it;
	};

	bool Object::iterator::operator==(const Object::iterator& other) {
		return it == other.it;
	};

	bool Object::iterator::operator!=(const Object::iterator& other) {
		return !(*this == other);
	};
}