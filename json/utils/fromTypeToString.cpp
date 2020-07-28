
#include "fromTypeToString.h"

std::string fromTypeToString(JSON::Type type) {
  switch (type)
  {
  case JSON::Type::NONE: return "NONE";
  case JSON::Type::STRING: return "STRING";
  case JSON::Type::NULL_: return "NULL_";
  case JSON::Type::NUMBER: return "NUMBER";
  case JSON::Type::BOOLEAN: return "BOOLEAN";
  case JSON::Type::ARRAY: return "ARRAY";
  case JSON::Type::OBJECT: return "OBJECT";
  default:
    throw std::logic_error("Unknown type:" + type);
  }
}