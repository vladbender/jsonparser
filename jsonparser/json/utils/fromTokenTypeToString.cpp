
#include "fromTokenTypeToString.h"

std::string fromTokenTypeToString(TokenType type) {
	switch (type)
	{
	case BRACE_LEFT: return "{";
	case BRACE_RIGHT: return "{";
	case BRACKET_LEFT: return "[";
	case BRACKET_RIGHT: return "]";
	case STRING_: return "STRING_";
	case NULL_: return "NULL_";
	case BOOLEAN: return "BOOLEAN";
	case COLON: return ":";
	case COMMA: return ",";
	case NUMBER: return "NUMBER";
	default:
		throw std::logic_error("Unknown type:" + type);
	}
}
