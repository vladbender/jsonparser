#pragma once

#include <vector>
#include <string>
#include <exception>
#include <stdexcept>

#include "Token.h"
#include "TokenType.h"
#include "../exceptions/Exceptions.h"

class Tokenizer {
public:
	Tokenizer(const std::string& s): json(s) {
		index = 0;
		alreadyRunned = false;
	}

	std::vector<Token> tokenize();

private:
	std::string json;
	size_t index;
	bool alreadyRunned;

	void skipWhiteSpaces() {
		while (
			index < json.size() &&
			(json[index] == ' ' ||
			json[index] == '\n' ||
			json[index] == '\r' ||
			json[index] == '\t')
		) {
			index++;
		}
	}

	void expectChar(char expected, char received) {
		if (expected != received) {
			throw JSON::ExpectedException(
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

	inline std::string extractString();

	inline std::string extractNumber();
	inline std::string extractOptionalMinus();
	inline std::string extractIntegerPart();
	inline std::string extractOptionalFractionalPart();
	inline std::string extractOptionalExponentialPart();

	void checkCurrentCharIsDigit() {
		if (!('0' <= json[index] && json[index] <= '9')) {
			throw JSON::ExpectedException("One of char: 0-9", std::string(1, json[index]));
		}
	}

	void checkCurrentCharIsSign() {
		if (!(json[index] == '+' || json[index] == '-')) {
			throw JSON::ExpectedException("One of char: +-", std::string(1, json[index]));
		}
	}
};
