#pragma once

#include <string>
#include <exception>

namespace JSON {
	class WrongLengthException : public std::exception {
	private:
		std::string message;
	public:
		WrongLengthException(std::string m) :
			std::exception(),
			message(m)
		{}

		const char* what() const {
			return message.c_str();
		}
	};
}