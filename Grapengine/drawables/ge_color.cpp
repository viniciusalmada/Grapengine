#include "ge_color.hpp"

#include "utils/ge_random.hpp"

using namespace GE;

Color Colors::RandomColor()
{
  return Color(
    Vec3{ Random::GenFloat(0.0, 1.0f), Random::GenFloat(0.0, 1.0f), Random::GenFloat(0.0, 1.0f) });
}
