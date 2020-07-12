
#include "unescapeQuotes.h"

// TODO не самый эффективный алгоритм
std::string unescapeQuotes(std::string& s) {
	std::string result = "";

	for (size_t i = 0; i < s.size() - 1;) {
		if (s[i] == '\\' && s[i + 1] == '"') {
			result += '"';
			i++;
		} else {
			result += s[i];
		}
		i++;
	}

	result += s[s.size() - 1];

	return result;
}