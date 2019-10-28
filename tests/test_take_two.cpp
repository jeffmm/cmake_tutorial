#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <take_two/take_two.hpp>

TEST_CASE("TakeTwo test") {
  SECTION("Addition") {
    REQUIRE(TakeTwo::Add(1, 9) == 10);
    REQUIRE(TakeTwo::Add(-9, 9) == 0);
  }
  SECTION("Subtraction") {
    REQUIRE(TakeTwo::Subtract(10, 5) == 5);
    REQUIRE(TakeTwo::Subtract(-10, 5) == -15);
  }
  SECTION("Multiplication") {
    REQUIRE(TakeTwo::Multiply(5, 0) == 0);
    REQUIRE(TakeTwo::Multiply(7, 7) == 49);
  }
  SECTION("Division") {
    REQUIRE(TakeTwo::Divide(9, 3) == 3);
    REQUIRE(TakeTwo::Divide(5, 1) == 5);
    REQUIRE(TakeTwo::Divide(3, 9) < 1);
    // Require thrown exception for divide by zero
    REQUIRE_THROWS(TakeTwo::Divide(9, 0));
    // Or we could have done the test this way
    try {
      TakeTwo::Divide(9, 0);
      // Fails if above succeeds without thrown exception
      REQUIRE(false);
    } catch (std::exception &e) {
      std::cout << "Successfully caught exception: " << e.what() << std::endl;
      REQUIRE(true);
    }
  }
}
