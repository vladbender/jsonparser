#pragma once

#include <vector>

#include "../types/Types.h"
#include "../utils/Utils.h"
#include "../exceptions/Exceptions.h"

#include "TokenType.h"
#include "Token.h"

using namespace JSON;

class Parser {
public:
	Parser(std::vector<Token> tokens) {
		// В таком случае вызывается конструктор копирования, не слишком ли это дорого?
		// Может передавать ссылку?
		this->tokens = tokens;
		result = NULL;
		index = 0;
	}

	AbstractObject* parse();

private:
	std::vector<Token> tokens;
	AbstractObject* result;
	size_t index;

	AbstractObject* parseUnknown();
	AbstractObject* parseArray();
	AbstractObject* parseObject();

	void excpectToken(TokenType expected, TokenType received) {
		if (expected != received) {
			throw ExcpectedException(
				fromTokenTypeToString(expected),
				fromTokenTypeToString(received)
			);
		}
	}

	void checkTokensOutOfRange() {
		if (index >= tokens.size()) {
			throw WrongLengthException("Unexpected end of JSON");
		}
	}
};
