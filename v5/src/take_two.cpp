#include <take_two/take_two.hpp>

float TakeTwo::Add(float a, float b) { return a + b; }
float TakeTwo::Subtract(float a, float b) { return a - b; }
float TakeTwo::Multiply(float a, float b) { return a * b; }
float TakeTwo::Divide(float a, float b) {
  if (b == 0) {
    throw std::overflow_error("Divide by zero exception!");
  }
  return a / b;
}
