
#include "Tokenizer.h"

std::vector<Token> Tokenizer::tokenize() {
	if (alreadyRunned) {
		throw std::logic_error("tokenize must run once");
	}
	alreadyRunned = true;

	std::vector<Token> result;

	while (index < json.size()) {
		
		skipWhiteSpaces();

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

		} else if (json[index] == '"') {
			index++;
			std::string raw = "";
			while (index < json.size()) {
				if (json[index] == '"' && index != 0 && json[index - 1] != '\\') {
					index++;
					break;
				}
				raw += json[index];
				index++;
			}
			result.push_back({ TokenType::STRING_, raw });

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

		} else if ('0' <= json[index] && json[index] <= '9') {
			std::string raw = "";
			// TODO сначала считаем числом любой набор из цифр и точек
			// В дальнейшем можно сразу его распарсить, чтобы прервать парсинг, если оно невалидно
			while (
				index < json.size() &&
				(('0' <= json[index] && json[index] <= '9') || json[index] == '.')
			) {
				raw += json[index];
				index++;
			}
			result.push_back({ TokenType::NUMBER, raw });

		} else {
			throw JSON::ExcpectedException("One of char: []{}:,\" or true/false/null", std::string(1, json[index]));
		}
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