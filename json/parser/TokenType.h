#pragma once

enum TokenType {
	BRACE_LEFT, // {
	BRACE_RIGHT, // }
	BRACKET_LEFT, // [
	BRACKET_RIGHT, // ]
	STRING, // "..."
	NULL_, // null
	BOOLEAN, // true, false
	COLON, // :
	COMMA, // ,
	NUMBER, // число
};
