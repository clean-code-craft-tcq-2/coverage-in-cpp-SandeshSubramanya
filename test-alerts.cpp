#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("Test infers breach accordingly to the limits") {
  // value, lower_limit, upper_limit
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(30, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(15, 20, 30) == NORMAL);
}
