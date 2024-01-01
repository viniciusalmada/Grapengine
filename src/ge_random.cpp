#include "ge_random.hpp"

namespace
{
  std::random_device rd{};
  std::mt19937 engine(rd());
  std::uniform_int_distribution<u32> int_dist(0, 0);
  std::uniform_real_distribution<float> real_dist(0, 0);
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

float Random::GenFloat(float min, float max)
{
  if (real_dist.a() != min || real_dist.b() != max)
  {
    std::uniform_real_distribution<float>::param_type p{ min, max };
    real_dist.param(p);
  }
  return real_dist(engine);
}
