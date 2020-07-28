#include <iostream>
#include "json/json.h"
#include "Tester.h"

void testCreateObject(Tester &tester) {
	tester.name("Create object");

	JSON::Object object;
	JSON::Array *array = new JSON::Array();

	object.set(std::string("arr"), array);

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

		auto arr = (JSON::Array*)(*obj)[std::string("arr")];

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
	} catch (JSON::ExpectedException &exp) {
		message = std::string(exp.what());
	} catch (JSON::WrongLengthException &wl) {
		message = std::string(wl.what());
	} catch (std::exception &e) {
		message = std::string(e.what());
	}

	tester.testEqual(message, std::string("Expected: <STRING>, but received: <[>"));
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

void testSpaceXLatestLaunch(Tester &tester) {
	tester.name("SpaceXLatestLaunch");

	std::string raw = "{\"fairings\":{\"reused\":null,\"recovery_attempt\":true,\"recovered\":true,\"ships\":[\"5ea6ed2e080df4000697c908\",\"5ea6ed2e080df4000697c907\"]},\"links\":{\"patch\":{\"small\":null,\"large\":null},\"reddit\":{\"campaign\":\"https://www.reddit.com/r/spacex/comments/hkbhqo/anasisii_launch_campaign_thread\",\"launch\":\"https://www.reddit.com/r/spacex/comments/hu6sci/rspacex_anasisii_official_launch_discussion/\",\"media\":\"https://www.reddit.com/r/spacex/comments/hun4pv/rspacex_anasisii_media_thread_photographer_contest/\",\"recovery\":null},\"flickr\":{\"small\":[],\"original\":[]},\"presskit\":null,\"webcast\":\"https://youtu.be/TshvZlQ7le8\",\"youtube_id\":\"TshvZlQ7le8\",\"article\":\"https://spaceflightnow.com/2020/07/20/spacex-delivers-south-koreas-first-military-satellite-into-on-target-orbit/\",\"wikipedia\":null},\"static_fire_date_utc\":\"2020-07-11T17:58:00.000Z\",\"static_fire_date_unix\":1594490280,\"tbd\":false,\"net\":false,\"window\":null,\"rocket\":\"5e9d0d95eda69973a809d1ec\",\"success\":true,\"failures\":[],\"details\":\"SpaceX will launch ANASIS-II, a South Korean geostationary military communication satellite from LC-39A, Kennedy Space Center. It will be South Korea's first dedicated military communications satellite. Falcon 9 will deliver the satellite to a geostationary transfer orbit. The booster is expected to land downrange on an ASDS.\",\"crew\":[],\"ships\":[\"5ea6ed2e080df4000697c908\",\"5ea6ed2e080df4000697c907\",\"5ea6ed2f080df4000697c90b\"],\"capsules\":[],\"payloads\":[\"5eb0e4d2b6c3bb0006eeb25b\"],\"launchpad\":\"5e9e4501f509094ba4566f84\",\"auto_update\":true,\"flight_number\":98,\"name\":\"ANASIS-II\",\"date_utc\":\"2020-07-20T21:30:00.000Z\",\"date_unix\":1595280600,\"date_local\":\"2020-07-20T17:30:00-04:00\",\"date_precision\":\"hour\",\"upcoming\":false,\"cores\":[{\"core\":\"5e9e28a7f3591817f23b2663\",\"flight\":2,\"gridfins\":true,\"legs\":true,\"reused\":true,\"landing_attempt\":true,\"landing_success\":true,\"landing_type\":\"ASDS\",\"landpad\":\"5e9e3033383ecbb9e534e7cc\"}],\"id\":\"5eb87d50ffd86e000604b394\"}";

	try {
		auto obj = *(JSON::Object*)JSON::parse(raw);

		auto details = *(JSON::String*)obj[std::string("details")];
		std::cout << "details: " << details.getValue() << std::endl;

		auto date_utc = *(JSON::String*)obj[std::string("date_utc")];
		std::cout << "date_utc: " << date_utc.getValue() << std::endl;

		auto links = *(JSON::Object*)obj[std::string("links")];
		auto reddit = *(JSON::Object*)links[std::string("reddit")];
		auto launch = *(JSON::String*)reddit[std::string("launch")];
		std::cout << "launch: " << launch.getValue() << std::endl;

		tester.testEqual(1, 1);
	} catch (std::exception &e) {
		tester.testEqual(std::string(e.what()), std::string());
	}
}

void testArraySize(Tester& tester) {
	tester.name("Test array size");

	try {
		auto arr1 = *(JSON::Array*)JSON::parse("[1,2,3,4]");
		tester.testEqual(arr1.size(), size_t(4));

		auto arr2 = *(JSON::Array*)JSON::parse("[]");
		tester.testEqual(arr2.size(), size_t(0));

		auto arr3 = *(JSON::Array*)JSON::parse("[\"one\", null, true, 123.456, {}, {}, {}]");
		tester.testEqual(arr3.size(), size_t(7));
	} catch (std::exception &e) {
		tester.testEqual(std::string(e.what()), std::string());
	}
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
	testSpaceXLatestLaunch(tester);
	testArraySize(tester);

	tester.summary();

	return 0;
}

