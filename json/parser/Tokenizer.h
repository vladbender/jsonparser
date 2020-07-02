#pragma once

#include <vector>
#include <string>
#include <exception>

#include "Token.h"
#include "TokenType.h"
#include "../exceptions/Exceptions.h"

class Tokenizer {
public:
	Tokenizer(std::string s): json(s) {
		index = 0;
		alreadyRunned = false;
	}

	std::vector<Token> tokenize();

private:
	std::string json;
	size_t index;
	bool alreadyRunned;

	void skipWhiteSpaces() {
		while (json[index] == ' ' || json[index] == '\n') {
			index++;
		}
	}

	void expectChar(char expected, char received) {
		if (expected != received) {
			throw JSON::ExcpectedException(
				std::string(1, expected),
				std::string(1, received)
			);
		}
	}

	void expectChars(std::vector<char> chars);

	void checkJSONOutOfRange() {
		if (index >= json.size()) {
			throw JSON::WrongLengthException("Unexpected end of JSON");
		}
	}
};
