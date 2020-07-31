#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <functional>

class TestException : public std::exception {
public:
	TestException(std::string message) :
		std::exception(),
		message(message) {}
	
	const char* what() const noexcept {
		return message.c_str();
	}
private:
	std::string message;
};

class NotEqualException : public TestException {
public:
	NotEqualException(std::string message) : TestException(message) {}
};

class EqualException : public TestException {
public:
	EqualException(std::string message) : TestException(message) {}
};

class Tester {
public:
	Tester() : failed(0), passed(0) {}
	void test(std::string name, std::function<void()> f);
	void testWithException(std::string name, std::string message, std::function<void()> f);
	template <typename T> void isEqual(T expected, T received);
	template <typename T> void isNotEqual(T expected, T received);
	void summary();
private:
	unsigned int failed;
	unsigned int passed;
};

void Tester::test(std::string name, std::function<void()> f) {
	try {
		f();
		std::cout << "Test \"" << name << "\" passed." << std::endl;
		passed++;
	} catch (NotEqualException &e) {
		std::cout << "Test \"" << name << "\" FAILED. " << e.what() << std::endl;
		failed++;
	} catch (EqualException &e) {
		std::cout << "Test \"" << name << "\" FAILED. " << e.what() << std::endl;
		failed++;
	} catch (std::exception &e) {
		std::cout << "Test \"" << name << "\" FAILED with unknown exception: "
			<< e.what() << std::endl;
		failed++;
	}
}

void Tester::testWithException(
	std::string name,
	std::string message,
	std::function<void()> f
) {
	try {
		f();
		std::cout << "Test \"" << name << "\" completed."
			<< "\n\tBUT SHOULD BE FAILED with message: <" << message << ">"
			<< std::endl;
		failed++;
	} catch (std::exception &e) {
		if (e.what() == message) {
			std::cout << "Test \"" << name << "\" passed." << std::endl;
			passed++;
		} else {
			std::cout << "Test \"" << name << "\" FAILED"
				<< "\n\tWith message: <" << e.what() << ">"
				<< "\n\tBut should with message: <" << message << ">"
				<< std::endl;
			failed++;
		}
	}
}

template <typename T>
void Tester::isEqual(T expected, T received) {
	if (expected != received) {
		std::ostringstream out;
		out << "\n\tExpected: <" << expected << ">\n\tSHOULD BE EQUAL\n\tReceived: <" << received << ">";
		throw NotEqualException(out.str());
	}
}

template <typename T>
void Tester::isNotEqual(T expected, T received) {
	if (expected == received) {
		std::ostringstream out;
		out << "\n\tExpected: <" << expected << ">\n\tSHOULDN'T BE EQUAL to\n\treceived: <" << received << ">";
		throw EqualException(out.str());
	}
}

void Tester::summary() {
	std::cout << "Passed: " << passed << " of " << passed + failed << "." << std::endl;
	std::cout << "Failed: " << failed << " of " << passed + failed << "." << std::endl;
}
