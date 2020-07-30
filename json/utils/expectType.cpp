
#include "expectType.h"

void expectType(const JSON::Type& expected, const JSON::Type& received) {
  if (expected != received) {
    throw JSON::ExpectedException(
      fromTypeToString(expected),
      fromTypeToString(received)
    );
  }
}