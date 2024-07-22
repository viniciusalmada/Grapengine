#ifndef GRAPENGINE_CYLINDER_HPP
#define GRAPENGINE_CYLINDER_HPP

#include "drawables/ge_color.hpp"
#include "drawables/ge_drawable.hpp"
#include "math/ge_vector.hpp"

namespace GE
{
  class Cylinder final
  {
  public:
    Cylinder(const Vec3& basePoint, f32 radius, const Vec3& direction, f32 height);

    const Drawable& GetDrawable() const;

  private:
    Drawable m_drawable;

  };
}

#endif // GRAPENGINE_CYLINDER_HPP
