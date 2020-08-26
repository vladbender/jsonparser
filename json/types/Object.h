#pragma once

#include <string>
#include <unordered_map>
#include <utility>

#include "AbstractObject.h"
#include "Number.h"
#include "String.h"
#include "Boolean.h"
#include "Array.h"

namespace JSON {
	class Array;
	class Object : public AbstractObject {
	public:
		Object() : AbstractObject() {
			type = Type::OBJECT;
		}
		~Object();
		AbstractObject* operator[](const std::string&);
		AbstractObject* get(const std::string& key) {
			return (*this)[key];
		}
		void set(const std::string&, AbstractObject*);
		std::string toString() const;
		Number* getNumber(const std::string& key);
		String* getString(const std::string& key);
		Boolean* getBoolean(const std::string& key);
		Array* getArray(const std::string& key);
		Object* getObject(const std::string& key);

		class iterator {
			public:
				iterator operator++();
				iterator operator++(int);
				// какие типы должны быть?
				std::pair<std::string, AbstractObject*> operator*();
				bool operator==(const iterator& other);
				bool operator!=(const iterator& other);
				iterator(const std::unordered_map<std::string, AbstractObject*>& values, bool isBegin);
				// конструктор копирования???
			private:
				std::unordered_map<std::string, AbstractObject*>::const_iterator it;
		};

		iterator begin() {
			return iterator(values, true);
		}

		iterator end() {
			return iterator(values, false);
		}
	private:
		std::unordered_map<std::string, AbstractObject*> values;
	};
}