
#include "parse.h"
#include "Parser.h"
#include "Tokenizer.h"
#include "../utils/Utils.h"

namespace JSON {
	AbstractObject* parse(const std::string& json) {
		Tokenizer tokenizer(json);
		auto tokens = tokenizer.tokenize();
		Parser parser(tokens);
		return parser.parse();
	}

	void expectType (const Type& expected, const Type& received) {
		if (expected != received) {
			throw ExpectedException(
				fromTypeToString(expected),
				fromTypeToString(received)
			);
		}
	}

	String* parseString(const std::string& json) {
		auto absObj = parse(json);
		expectType(absObj->getType(), Type::STRING);
		return (String*)absObj;
	}

	Number* parseNumber(const std::string& json) {
		auto absObj = parse(json);
		expectType(absObj->getType(), Type::NUMBER);
		return (Number*)absObj;
	}

	Boolean* parseBoolean(const std::string& json) {
		auto absObj = parse(json);
		expectType(absObj->getType(), Type::BOOLEAN);
		return (Boolean*)absObj;
	}

	Array* parseArray(const std::string& json) {
		auto absObj = parse(json);
		expectType(absObj->getType(), Type::ARRAY);
		return (Array*)absObj;
	}

	Object* parseObject(const std::string& json) {
		auto absObj = parse(json);
		expectType(absObj->getType(), Type::OBJECT);
		return (Object*)absObj;
	}
}
