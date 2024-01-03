#ifndef GRAPHICENGINE3D_GE_RANDOM_HPP
#define GRAPHICENGINE3D_GE_RANDOM_HPP

namespace Random
{
  GE3D u32 GenInt(u32 min = std::numeric_limits<u32>::min(),
                  u32 max = std::numeric_limits<u32>::max());

  GE3D float GenFloat(float min = std::numeric_limits<float>::min(),
                      float max = std::numeric_limits<float>::max());
}

#endif // GRAPHICENGINE3D_GE_RANDOM_HPP
