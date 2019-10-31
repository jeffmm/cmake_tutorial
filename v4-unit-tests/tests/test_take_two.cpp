#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <take_two/take_two.hpp>

TEST_CASE("TakeTwo test") {
  SECTION("Addition") {
    REQUIRE(TakeTwo::Add(1, 9) == 10);
    REQUIRE(TakeTwo::Add(-9, 9) == 0);
  }
}
