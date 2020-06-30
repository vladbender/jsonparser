#pragma once

#include <string>
#include <exception>

namespace JSON {
	class ExcpectedException : public std::exception {
	private:
		std::string message;

	public:
		ExcpectedException(std::string expected, std::string received) :
			std::exception()
		{
			message = "Expected: <" + expected + ">, but received: <" + received + ">";
		}

		const char* what() const {
			return message.c_str();
		}
	};
}
