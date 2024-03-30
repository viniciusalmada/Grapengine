#ifndef GRAPENGINE_CYLINDER_HPP
#define GRAPENGINE_CYLINDER_HPP

#include "ge_drawable.hpp"

#include <math/ge_vector.hpp>
namespace GE
{
  struct Color;
  class Texture2D;
  class Cylinder : public Drawable
  {
  public:
    static Ref<Cylinder> Make(const Ref<IShaderProgram>& shader,
                              f32 radius,
                              const Vec3& basePoint,
                              const Vec3& direction,
                              f32 height,
                              Color color,
                              const Ref<Texture2D>& texture2D);

    GE3D Cylinder(const Ref<IShaderProgram>& shader,
                  f32 radius,
                  const Vec3& basePoint,
                  const Vec3& direction,
                  f32 height,
                  Color color,
                  Ref<Texture2D> texture2D);
    ~Cylinder() override;

    void Draw() const override;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_CYLINDER_HPP
