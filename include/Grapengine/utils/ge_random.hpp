#ifndef GRAPENGINE_RANDOM_HPP
#define GRAPENGINE_RANDOM_HPP

#include "core/ge_config.hpp"
#include "core/ge_type_aliases.hpp"

#include <limits>

namespace GE::Random
{
  GE3D u32 GenInt(u32 min = std::numeric_limits<u32>::min(),
                  u32 max = std::numeric_limits<u32>::max());

  GE3D float GenFloat(float min = std::numeric_limits<float>::min(),
                      float max = std::numeric_limits<float>::max());
}

#endif // GRAPENGINE_RANDOM_HPP
