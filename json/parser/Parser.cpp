
#include "Parser.h"

AbstractObject* Parser::parse() {
	if (result != NULL) {
		// Если функция parse уже вызывалась - возвращаем результат
		return result;
	}

	auto res = parseUnknown();

	if (index != tokens.size()) {
		/**
		 * TODO возможно, стоит возвращать результат, но при этом устанавливать флаг,
		 * что не вся строка была распарсена
		 */
		throw WrongLengthException("Not all characters parsed");
	}

	return result = res;
}

AbstractObject* Parser::parseUnknown() {
	checkTokensOutOfRange();

	auto &type = tokens[index].type;

	switch (type) {
	case TokenType::STRING: {
		auto str = new String(unescapeQuotes(tokens[index].rawValue));
		index++;
		return str;
	}

	case TokenType::NULL_: {
		auto n = new Null();
		index++;
		return n;
	}

	case TokenType::BOOLEAN: {
		auto b = new Boolean(tokens[index].rawValue[0] == 't' ? true : false);
		index++;
		return b;
	}

	case TokenType::NUMBER: {
		auto d = std::stod(tokens[index].rawValue);
		auto num = new Number(d);
		index++;
		return num;
	}

	case TokenType::BRACKET_LEFT:
		return parseArray();

	case TokenType::BRACE_LEFT:
		return parseObject();

	default:
		throw JSON::ExpectedException(
			"One of STRING, NULL_, BOOLEAN or NUMBER",
			fromTokenTypeToString(type)
		);
	}
}

AbstractObject* Parser::parseArray() {
	excpectToken(TokenType::BRACKET_LEFT, tokens[index].type);
	index++;
	checkTokensOutOfRange();
	auto array = new Array();
	if (tokens[index].type == TokenType::BRACKET_RIGHT) {
		index++;
		return array;
	}
	while (index < tokens.size()) {
		auto next = parseUnknown();
		array->push(next);
		checkTokensOutOfRange();
		if (tokens[index].type == TokenType::BRACKET_RIGHT) {
			break;
		}
		excpectToken(TokenType::COMMA, tokens[index].type);
		index++;
	}
	checkTokensOutOfRange();
	index++;
	return array;
}

AbstractObject* Parser::parseObject() {
	excpectToken(TokenType::BRACE_LEFT, tokens[index].type);
	index++;
	checkTokensOutOfRange();
	auto obj = new Object();
	if (tokens[index].type == TokenType::BRACE_RIGHT) {
		index++;
		return obj;
	}
	while (index < tokens.size()) {
		excpectToken(TokenType::STRING, tokens[index].type);
		auto key = unescapeQuotes(tokens[index].rawValue);
		index++;
		checkTokensOutOfRange();
		excpectToken(TokenType::COLON, tokens[index].type);
		index++;
		auto value = parseUnknown();
		obj->set(key, value);
		checkTokensOutOfRange();
		if (tokens[index].type == TokenType::BRACE_RIGHT) {
			break;
		}
		excpectToken(TokenType::COMMA, tokens[index].type);
		index++;
	}
	checkTokensOutOfRange();
	index++;
	return obj;
}
