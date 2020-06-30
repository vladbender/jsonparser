#pragma once

#include <iostream>
#include <string>

// Из за отсутствия фреймворка для тестирования, делаем его сами
class Tester {
public:
	Tester() {
		currentTestName = "";
		passed = 0;
		failed = 0;
		step = 1;
	}

	void name(std::string testName) {
		currentTestName = testName;
		step = 1;
	}

	template <typename T>
	void testEqual(T expected, T received) {
		if (expected == received) {
			std::cout << "TEST \"" << currentTestName << "\"" << " STEP:" << step << " passed." << std::endl;
			passed++;
		} else {
			std::cout << "TEST \"" << currentTestName << "\"" << " STEP:" << step << " FAILED !!!!!" << std::endl;
			std::cout << "\tEXPECTED: \"" << expected << "\"" << std::endl <<
				"\tRECEIVED: \"" << received << "\"" << std::endl;
			failed++;
		}
		step++;
	}

	void summary() {
		std::cout << "Passed: " << passed << " of " << passed + failed << std::endl;
		std::cout << "Failed: " << failed << " of " << passed + failed << std::endl;
	}

private:
	std::string currentTestName;
	int passed;
	int failed;
	int step;
};