
#include "Tokenizer.h"

std::vector<Token> Tokenizer::tokenize() {
	if (alreadyRunned) {
		throw std::logic_error("tokenize must run once");
	}
	alreadyRunned = true;

	std::vector<Token> result;

	skipWhiteSpaces();

	while (index < json.size()) {

		if (json[index] == '{') {
			result.push_back({ TokenType::BRACE_LEFT, "{" });
			index++;

		} else if (json[index] == '}') {
			result.push_back({ TokenType::BRACE_RIGHT, "}" });
			index++;

		} else if (json[index] == '[') {
			result.push_back({ TokenType::BRACKET_LEFT, "[" });
			index++;

		} else if (json[index] == ']') {
			result.push_back({ TokenType::BRACKET_RIGHT, "]" });
			index++;

		} else if (json[index] == ':') {
			result.push_back({ TokenType::COLON, ":" });
			index++;

		} else if (json[index] == ',') {
			result.push_back({ TokenType::COMMA, "," });
			index++;

		} else if (json[index] == 't') {
			index++;
			expectChars({ 'r', 'u', 'e' });
			result.push_back({ TokenType::BOOLEAN, "true" });

		} else if (json[index] == 'f') {
			index++;
			expectChars({ 'a', 'l', 's', 'e' });
			result.push_back({ TokenType::BOOLEAN, "false" });

		} else if (json[index] == 'n') {
			index++;
			expectChars({ 'u', 'l', 'l' });
			result.push_back({ TokenType::NULL_, "null" });

		} else if (json[index] == '"') {
			std::string raw = extractString();
			result.push_back({ TokenType::STRING, raw });

		} else if ('0' <= json[index] && json[index] <= '9' || json[index] == '-') {
			std::string raw = extractNumber();
			result.push_back({ TokenType::NUMBER, raw });

		} else {
			throw JSON::ExpectedException("One of char: []{}:+-,\" digits or true/false/null", std::string(1, json[index]));
		}

		skipWhiteSpaces();
	}

	return result;
}

void Tokenizer::expectChars(std::vector<char> chars) {
	for (char c : chars) {
		checkJSONOutOfRange();
		expectChar(c, json[index]);
		index++;
	}
}

inline std::string Tokenizer::extractString() {
	index++;
	std::string raw = "";
	while (index < json.size()) {
		if (json[index] == '"' && index != 0 && json[index - 1] != '\\') {
			index++;
			break;
		}
		raw += json[index++];
	}
	return raw;
}

inline std::string Tokenizer::extractNumber() {
	std::string raw = "";
	/**
	 * Валидным числом в JSON считается строка, состящая из символов:
	 * 1) - (опционален)
	 * 2) 0 или ( (1-9) + любое количество цифр (0-9) ) (число не может начинаться с нуля)
	 * 3) . (опционально) + любое количество цифр (0-9) (если точка есть то цифры обязательны)
	 * 4) Опциональный пункт E или e, затем обязательно + или -, затем любое количество цифр 0-9
	 *    (если есть в начале Е или е, то далее обязательны +- и хотя бы одна цифра)
	 *    пункт может существовать независимо от пункта 3.
	 */

	raw += extractOptionalMinus();
	raw += extractIntegerPart();
	if (index >= json.size()) {
		return raw;
	}
	raw += extractOptionalFractionalPart();
	if (index >= json.size()) {
		return raw;
	}
	raw += extractOptionalExponentialPart();
	return raw;
}

inline std::string Tokenizer::extractOptionalMinus() {
	if (json[index] == '-') {
		return std::string(1, json[index++]);
	}
	checkJSONOutOfRange();
	return "";
}

inline std::string Tokenizer::extractIntegerPart() {
	std::string raw = "";
	if (json[index] == '0') {
		raw += json[index++];
	} else if ('1' <= json[index] && json[index] <= '9') {
		while (index < json.size() && '0' <= json[index] && json[index] <= '9') {
			raw += json[index++];
		}	
	} else {
		throw JSON::ExpectedException("One of char: 0-9", std::string(1, json[index]));
	}
	return raw;
}

inline std::string Tokenizer::extractOptionalFractionalPart() {
	std::string raw = "";
	if (json[index] == '.') {
		raw += json[index++];
		checkJSONOutOfRange();
		checkCurrentCharIsDigit();
		while (index < json.size() && '0' <= json[index] && json[index] <= '9') {
			raw += json[index++];
		}
	}
	return raw;
}

inline std::string Tokenizer::extractOptionalExponentialPart() {
	std::string raw = "";
	if (json[index] == 'E' || json[index] == 'e') {
		raw += json[index++];
		checkJSONOutOfRange();
		checkCurrentCharIsSign();
		raw += json[index++];
		checkJSONOutOfRange();
		checkCurrentCharIsDigit();
		while (index < json.size() && '0' <= json[index] && json[index] <= '9') {
			raw += json[index++];
		}
	}
	return raw;
}