#pragma once

#include <string>
#include <exception>

namespace JSON {
	class ExpectedException : public std::exception {
	private:
		std::string message;

	public:
		ExpectedException(std::string expected, std::string received) :
			std::exception()
		{
			message = "Expected: <" + expected + ">, but received: <" + received + ">";
		}

		const char* what() const {
			return message.c_str();
		}
	};
}
