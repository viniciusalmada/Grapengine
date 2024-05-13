#include "utils/ge_random.hpp"

#include <math/ge_arithmetic.hpp>

using namespace GE;

u32 Random::GenInt(u32 min, u32 max)
{
  if (Get().m_int_dist.a() != min || Get().m_int_dist.b() != max)
  {
    const std::uniform_int_distribution<u32>::param_type p{ min, max };
    Get().m_int_dist.param(p);
  }
  return Get().m_int_dist(Get().m_engine);
}

f32 Random::GenFloat(f32 min, f32 max)
{
  if (!Arithmetic::IsEqual(Get().m_real_dist.a(), min) ||
      !Arithmetic::IsEqual(Get().m_real_dist.b(), max))
  {
    const std::uniform_real_distribution<f32>::param_type p{ min, max };
    Get().m_real_dist.param(p);
  }
  return Get().m_real_dist(Get().m_engine);
}

Random& Random::Get()
{
  static Random random;
  return random;
}

Random::Random() :
    m_engine(m_rd()),
    m_int_dist(std::uniform_int_distribution<u32>{ 0, 0 }),
    m_real_dist(std::uniform_real_distribution<f32>{ 0, 0 })
{
}
