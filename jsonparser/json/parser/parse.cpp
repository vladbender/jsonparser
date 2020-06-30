
#include "parse.h"
#include "Parser.h"
#include "Tokenizer.h"

namespace JSON {
	AbstractObject* parse(std::string json) {
		Tokenizer tokenizer(json);

		auto tokens = tokenizer.tokenize();

		Parser parser(tokens);

		return parser.parse();
	}
}
