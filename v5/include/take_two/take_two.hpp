#ifndef _TAKE_TWO_HPP_
#define _TAKE_TWO_HPP_

#include <iostream>
#include <stdexcept>

/// Take two floating point numbers and perform some simple arithmetic.
/** This class allows for the computation of trivial arithmetic on two numbers.
 */
class TakeTwo {
public:
  /// Add two numbers.
  /**
    \param a the first argument.
    \param b the second argument.
    \return A float a added to b
  */
  static float Add(float a, float b);
  /// Subtract two numbers.
  /**
    \param a the first argument.
    \param b the second argument.
    \return A float b subtracted from a
  */
  static float Subtract(float a, float b);
  /// Multiply two numbers.
  /**
    \param a the first argument.
    \param b the second argument.
    \return A float a multiplied by b
  */
  static float Multiply(float a, float b);
  /// Divide two numbers.
  /**
    \param a the first argument.
    \param b the second argument.
    \return A float a divided by b
  */
  static float Divide(float a, float b);
};

#endif // _TAKE_TWO_HPP_
