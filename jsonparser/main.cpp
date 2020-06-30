#include <iostream>
#include "json/json.h"
#include "Tester.h"

void testCreateObject(Tester &tester) {
	tester.name("Create object");

	JSON::Object object;
	JSON::Array *array = new JSON::Array();

	object.set("arr", array);

	array->push(new JSON::String("this is \" a string"));
	array->push(new JSON::Null());
	array->push(new JSON::Number(666));
	array->push(new JSON::Boolean(true));
	array->push(new JSON::Array());
	array->push(new JSON::Object());

	std::string s = object.toString();

	tester.testEqual(s, std::string("{ \"arr\": [ \"this is \\\" a string\", null, 666, true, [], {} ] }"));
}

void testParseObject(Tester &tester) {
	tester.name("Parse Object");

	try {
		auto obj = (JSON::Object*)JSON::parse("{ \"arr\": [ \"this is \\\" a string\", null, 666, true, [], {} ] }");

		tester.testEqual(obj->getType(), JSON::Type::OBJECT);
		
		if (obj->getType() != JSON::Type::OBJECT) {
			return;
		}

		auto arr = (JSON::Array*)(*obj)["arr"];

		if (arr == nullptr) {
			tester.testEqual("arr pointer", "is nullptr");
			return;
		}

		tester.testEqual(arr->getType(), JSON::Type::ARRAY);

		if (arr->getType() != JSON::Type::ARRAY) {
			return;
		}

		auto num = (JSON::Number*)(*arr)[2];

		if (num == nullptr) {
			tester.testEqual("num pointer", "is nullptr");
			return;
		}

		tester.testEqual(num->getType(), JSON::Type::NUMBER);

		if (num->getType() != JSON::Type::NUMBER) {
			return;
		}

		tester.testEqual(num->getValue(), (double)666);

		delete obj;
	} catch (std::exception &e) {
		tester.testEqual(std::string(""), std::string(e.what()));
	}
}

void testExpectedString(Tester &tester) {
	tester.name("Expected String");

	std::string message = "";

	try {
		auto obj = JSON::parse("{[}");

		std::cout << obj->getType() << std::endl;
	} catch (JSON::ExcpectedException &exp) {
		message = std::string(exp.what());
	} catch (JSON::WrongLengthException &wl) {
		message = std::string(wl.what());
	} catch (std::exception &e) {
		message = std::string(e.what());
	}

	tester.testEqual(message, std::string("Expected: <STRING_>, but received: <[>"));
}

void testNotAllCharactersParsed(Tester &tester) {
	tester.name("Not all characters parsed");

	std::string message = "";

	try {
		auto obj = JSON::parse("{}{");

		std::cout << obj->getType() << std::endl;
	} catch (std::exception &e) {
		message = std::string(e.what());
	}

	tester.testEqual(message, std::string("Not all characters parsed"));
}

void testUnexpectedEndOfJSON(Tester &tester) {
	tester.name("Unexpected end of JSON");

	std::string message = "";

	try {
		auto obj = JSON::parse("{\"key\":");

		std::cout << obj->getType() << std::endl;
	} catch (std::exception &e) {
		message = std::string(e.what());
	}

	tester.testEqual(message, std::string("Unexpected end of JSON"));
}

void testExpectedTrue(Tester &tester) {
	tester.name("Expected true");

	std::string message = "";

	try {
		auto obj = JSON::parse("{\"key\":trqq}");

		std::cout << obj->getType() << std::endl;
	} catch (std::exception &e) {
		message = std::string(e.what());
	}

	tester.testEqual(message, std::string("Expected: <u>, but received: <q>"));
}

void testExpectedOneOf(Tester &tester) {
	tester.name("Expected one of");

	std::string message = "";

	try {
		auto obj = JSON::parse("{\"key\":qqq}");

		std::cout << obj->getType() << std::endl;
	} catch (std::exception &e) {
		message = std::string(e.what());
	}

	tester.testEqual(message, std::string("Expected: <One of char: []{}:,\" or true/false/null>, but received: <q>"));
}

void testJustAString(Tester &tester) {
	tester.name("Just a string");

	std::string source = "\"just a string\"";

	try {
		auto obj = JSON::parse(source);

		tester.testEqual(obj->toString(), source);
	} catch (std::exception &e) {
		tester.testEqual(std::string(""), std::string(e.what()));
	}
}

void testNull(Tester &tester) {
	tester.name("null");

	std::string source = "null";

	try {
		auto obj = JSON::parse(source);

		tester.testEqual(obj->toString(), source);
	} catch (std::exception &e) {
		tester.testEqual(std::string(""), std::string(e.what()));
	}
}

void testUndefined(Tester &tester) {
	tester.name("undefined");

	std::string message = "";

	try {
		auto obj = JSON::parse("undefined");

		std::cout << obj->getType() << std::endl;
	} catch (std::exception &e) {
		message = std::string(e.what());
	}

	tester.testEqual(message, std::string("Expected: <One of char: []{}:,\" or true/false/null>, but received: <u>"));
}

int main() {
	Tester tester;

	testCreateObject(tester);
	testExpectedString(tester);
	testNotAllCharactersParsed(tester);
	testUnexpectedEndOfJSON(tester);
	testExpectedTrue(tester);
	testExpectedOneOf(tester);
	testJustAString(tester);
	testNull(tester);
	testUndefined(tester);
	testParseObject(tester);

	tester.summary();

	return 0;
}

