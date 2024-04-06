#ifndef GRAPENGINE_RANDOM_HPP
#define GRAPENGINE_RANDOM_HPP

#include "core/ge_config.hpp"
#include "core/ge_type_aliases.hpp"

#include <limits>

namespace GE::Random
{
  GE3D u32 GenInt(u32 min = std::numeric_limits<u32>::min(),
                  u32 max = std::numeric_limits<u32>::max());

  GE3D f32 GenFloat(f32 min = std::numeric_limits<f32>::min(),
                      f32 max = std::numeric_limits<f32>::max());
}

#endif // GRAPENGINE_RANDOM_HPP
