#include "math/ge_arithmetic.hpp"

bool Arithmetic::IsEqual(float a, float b)
{
  return std::fabs(a - b) < std::numeric_limits<float>::epsilon();
}