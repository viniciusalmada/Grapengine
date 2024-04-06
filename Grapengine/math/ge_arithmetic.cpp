#include "math/ge_arithmetic.hpp"

bool Arithmetic::IsEqual(f32 a, f32 b)
{
  return std::fabs(a - b) < std::numeric_limits<f32>::epsilon();
}