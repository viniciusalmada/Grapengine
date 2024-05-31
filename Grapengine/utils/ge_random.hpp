#ifndef GRAPENGINE_RANDOM_HPP
#define GRAPENGINE_RANDOM_HPP

#include "core/ge_config.hpp"
#include "core/ge_type_aliases.hpp"

namespace GE
{
  class Random
  {
  public:
    static void Init() { Get(); }

    static u32 GenInt(u32 min = std::numeric_limits<u32>::min(),
                      u32 max = std::numeric_limits<u32>::max());

    static f32 GenFloat(f32 min = std::numeric_limits<f32>::min(),
                        f32 max = std::numeric_limits<f32>::max());

  private:
    Random();
    static Random& Get();

    std::random_device m_rd;
    std::mt19937 m_engine;
    std::uniform_int_distribution<u32> m_int_dist;
    std::uniform_real_distribution<f32> m_real_dist;
  };
}

#endif // GRAPENGINE_RANDOM_HPP
