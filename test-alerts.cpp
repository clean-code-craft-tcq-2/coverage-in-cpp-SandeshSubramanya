#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("Test infers breach accordingly to the limits") {
  // value, lower_limit, upper_limit
  #define Lower_limit 20
  #define Upper_limit 30
  REQUIRE(inferBreach(12, Lower_limit, Upper_limit) == TOO_LOW);
  REQUIRE(inferBreach(30, Lower_limit, Upper_limit) == TOO_HIGH);
  REQUIRE(inferBreach(15, Lower_limit, Upper_limit) == NORMAL);
}
