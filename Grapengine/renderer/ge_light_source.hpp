#ifndef GRAPENGINE_GE_LIGHT_SOURCE_HPP
#define GRAPENGINE_GE_LIGHT_SOURCE_HPP
#include "drawables/ge_color.hpp"
#include "math/ge_vector.hpp"

namespace GE
{
  struct LightSource
  {
    Vec3 position;
    Color color;
    f32 light_str;
    f32 specular_str;
    u32 shininess;

    bool operator==(const LightSource& other) const;
  };
}

#endif // GRAPENGINE_GE_LIGHT_SOURCE_HPP
