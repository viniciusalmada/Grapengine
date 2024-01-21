#ifndef GRAPENGINE_CYLINDER_HPP
#define GRAPENGINE_CYLINDER_HPP

#include "ge_drawable.hpp"

#include <math/ge_vector.hpp>
namespace GE
{
  struct Color;
  class Cylinder : public Drawable
  {
  public:
    GE3D Cylinder(Shaders shader,
                  float radius,
                  const Vec3& basePoint,
                  const Vec3& direction,
                  float height,
                  Color color);
    ~Cylinder() override;

    void Draw() const override;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_CYLINDER_HPP
