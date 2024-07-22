#ifndef GRAPENGINE_GE_LIGHT_SOURCE_HPP
#define GRAPENGINE_GE_LIGHT_SOURCE_HPP

namespace GE
{
  struct LightSource
  {
    Vec3 position;
    Color color;
    f32 light_str;
    f32 specular_str;
    f32 shininess;
  };
}

#endif // GRAPENGINE_GE_LIGHT_SOURCE_HPP
