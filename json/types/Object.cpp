
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
}