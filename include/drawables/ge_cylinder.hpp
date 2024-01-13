#ifndef GRAPHICENGINE3D_GE_CYLINDER_HPP
#define GRAPHICENGINE3D_GE_CYLINDER_HPP

#include "ge_drawable.hpp"

#include <math/ge_vector.hpp>

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

#endif // GRAPHICENGINE3D_GE_CYLINDER_HPP
