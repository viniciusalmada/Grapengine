#include "utils/ge_random.hpp"

#include <math/ge_arithmetic.hpp>

using namespace GE;

namespace
{
  std::random_device rd{};
  std::mt19937 engine(rd());
  std::uniform_int_distribution<u32> int_dist(0, 0);
  std::uniform_real_distribution<f32> real_dist(0, 0);
}

u32 Random::GenInt(u32 min, u32 max)
{
  if (int_dist.a() != min || int_dist.b() != max)
  {
    std::uniform_int_distribution<u32>::param_type p{ min, max };
    int_dist.param(p);
  }
  return int_dist(engine);
}

f32 Random::GenFloat(f32 min, f32 max)
{
  if (!Arithmetic::IsEqual(real_dist.a(), min) || !Arithmetic::IsEqual(real_dist.b(), max))
  {
    std::uniform_real_distribution<f32>::param_type p{ min, max };
    real_dist.param(p);
  }
  return real_dist(engine);
}
