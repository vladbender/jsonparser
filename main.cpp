#include <iostream>
#include "json/json.h"
#include "Tester.h"

int main() {
	Tester tester;

	tester.test("Create object", [&]() {
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
		tester.isEqual(s, std::string("{ \"arr\": [ \"this is \\\" a string\", null, 666, true, [], {} ] }"));
	});

	tester.test("Parse Object", [&]() {
		auto obj = JSON::parseObject("{ \"arr\": [ \"this is \\\" a string\", null, 666, true, [], {} ] }");
		auto arr = obj->getArray(std::string("arr"));
		tester.isNotEqual<JSON::Array*>(arr, nullptr);
		auto str = arr->stringAt(0);
		tester.isEqual<std::string>(str->getValue(), "this is \" a string");
		auto num = arr->numberAt(2);
		tester.isEqual<double>(num->getValue(), 666);
		auto b = arr->booleanAt(3);
		tester.isEqual(b->getValue(), true);
		auto nestedArray = arr->arrayAt(4);
		tester.isEqual<size_t>(nestedArray->size(), 0);
		auto nestedObject = arr->objectAt(5);
		tester.isEqual(nestedObject->getType(), JSON::Type::OBJECT);
		delete obj;
	});

	tester.testWithException(
		"Expected String",
		"Expected: <STRING>, but received: <[>",
		[&]() {
			auto obj = JSON::parse("{[}");
			std::cout << obj->getType() << std::endl;
		}
	);

	tester.testWithException(
		"Exception not all characters parsed",
		"Not all characters parsed",
		[&]() {
			auto obj = JSON::parse("{}{");
			std::cout << obj->getType() << std::endl;
		}
	);

	tester.testWithException(
		"Exception unexpected end of JSON",
		"Unexpected end of JSON",
		[&]() {
			auto obj = JSON::parse("{\"key\":");
			std::cout << obj->getType() << std::endl;
		}
	);

	tester.testWithException(
		"Expected true",
		"Expected: <u>, but received: <q>",
		[&]() {
			auto obj = JSON::parse("{\"key\":trqq}");
			std::cout << obj->getType() << std::endl;
		}
	);

	tester.testWithException(
		"Expected one of",
		"Expected: <One of char: []{}:,\" or true/false/null>, but received: <q>",
		[&]() {
			auto obj = JSON::parse("{\"key\":qqq}");
			std::cout << obj->getType() << std::endl;
		}
	);

	tester.test("Just a string", [&]() {
		std::string source = "\"just a string\"";
		auto obj = JSON::parseString(source);
		tester.isEqual(obj->toString(), source);
	});

	tester.test("null", [&]() {
		std::string source = "null";
		auto obj = JSON::parse(source);
		tester.isEqual(obj->toString(), source);
	});

	tester.testWithException(
		"undefined",
		"Expected: <One of char: []{}:,\" or true/false/null>, but received: <u>",
		[&]() {
			auto obj = JSON::parse("undefined");
			std::cout << obj->getType() << std::endl;
		}
	);

	tester.test("SpaceX latest launch", [&]() {
		std::string raw = "{\"fairings\":{\"reused\":null,\"recovery_attempt\":true,\"recovered\":true,\"ships\":[\"5ea6ed2e080df4000697c908\",\"5ea6ed2e080df4000697c907\"]},\"links\":{\"patch\":{\"small\":null,\"large\":null},\"reddit\":{\"campaign\":\"https://www.reddit.com/r/spacex/comments/hkbhqo/anasisii_launch_campaign_thread\",\"launch\":\"https://www.reddit.com/r/spacex/comments/hu6sci/rspacex_anasisii_official_launch_discussion/\",\"media\":\"https://www.reddit.com/r/spacex/comments/hun4pv/rspacex_anasisii_media_thread_photographer_contest/\",\"recovery\":null},\"flickr\":{\"small\":[],\"original\":[]},\"presskit\":null,\"webcast\":\"https://youtu.be/TshvZlQ7le8\",\"youtube_id\":\"TshvZlQ7le8\",\"article\":\"https://spaceflightnow.com/2020/07/20/spacex-delivers-south-koreas-first-military-satellite-into-on-target-orbit/\",\"wikipedia\":null},\"static_fire_date_utc\":\"2020-07-11T17:58:00.000Z\",\"static_fire_date_unix\":1594490280,\"tbd\":false,\"net\":false,\"window\":null,\"rocket\":\"5e9d0d95eda69973a809d1ec\",\"success\":true,\"failures\":[],\"details\":\"SpaceX will launch ANASIS-II, a South Korean geostationary military communication satellite from LC-39A, Kennedy Space Center. It will be South Korea's first dedicated military communications satellite. Falcon 9 will deliver the satellite to a geostationary transfer orbit. The booster is expected to land downrange on an ASDS.\",\"crew\":[],\"ships\":[\"5ea6ed2e080df4000697c908\",\"5ea6ed2e080df4000697c907\",\"5ea6ed2f080df4000697c90b\"],\"capsules\":[],\"payloads\":[\"5eb0e4d2b6c3bb0006eeb25b\"],\"launchpad\":\"5e9e4501f509094ba4566f84\",\"auto_update\":true,\"flight_number\":98,\"name\":\"ANASIS-II\",\"date_utc\":\"2020-07-20T21:30:00.000Z\",\"date_unix\":1595280600,\"date_local\":\"2020-07-20T17:30:00-04:00\",\"date_precision\":\"hour\",\"upcoming\":false,\"cores\":[{\"core\":\"5e9e28a7f3591817f23b2663\",\"flight\":2,\"gridfins\":true,\"legs\":true,\"reused\":true,\"landing_attempt\":true,\"landing_success\":true,\"landing_type\":\"ASDS\",\"landpad\":\"5e9e3033383ecbb9e534e7cc\"}],\"id\":\"5eb87d50ffd86e000604b394\"}";
		auto obj = JSON::parseObject(raw);
		auto details = obj->getString(std::string("details"));
		tester.isEqual<std::string>(details->getValue(), "SpaceX will launch ANASIS-II, a South Korean geostationary military communication satellite from LC-39A, Kennedy Space Center. It will be South Korea's first dedicated military communications satellite. Falcon 9 will deliver the satellite to a geostationary transfer orbit. The booster is expected to land downrange on an ASDS.");
		auto date_utc = obj->getString(std::string("date_utc"));
		tester.isEqual<std::string>(date_utc->getValue(), "2020-07-20T21:30:00.000Z");
		auto links = obj->getObject(std::string("links"));
		auto reddit = links->getObject(std::string("reddit"));
		auto launch = reddit->getString(std::string("launch"));
		tester.isEqual<std::string>(launch->getValue(), "https://www.reddit.com/r/spacex/comments/hu6sci/rspacex_anasisii_official_launch_discussion/");
		delete obj;
	});

	tester.test("Array size", [&]() {
		auto arr1 = JSON::parseArray("[1,2,3,4]");
		tester.isEqual<size_t>(arr1->size(), 4);
		auto arr2 = JSON::parseArray("[]");
		tester.isEqual<size_t>(arr2->size(), 0);
		auto arr3 = JSON::parseArray("[\"one\", null, true, 123.456, {}, {}, {}]");
		tester.isEqual<size_t>(arr3->size(), 7);
		delete arr1;
		delete arr2;
		delete arr3;
	});

	tester.summary();

	return 0;
}
