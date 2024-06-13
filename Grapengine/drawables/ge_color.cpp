#include "ge_color.hpp"

#include "utils/ge_random.hpp"

using namespace GE;

Color Colors::RandomColor()
{
  return Color(
    Vec3{ Random::GenFloat(0.0, 1.0f), Random::GenFloat(0.0, 1.0f), Random::GenFloat(0.0, 1.0f) });
}

bool Color::operator==(const Color& rhs) const
{
  return R == rhs.R && G == rhs.G && B == rhs.B && A == rhs.A;
}

bool Color::operator!=(const Color& rhs) const
{
  return !(rhs == *this);
}
