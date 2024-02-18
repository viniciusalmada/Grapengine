#ifndef GRAPENGINE_CIRCLE_SHAPE_HPP
#define GRAPENGINE_CIRCLE_SHAPE_HPP

#include "ge_color.hpp"
#include "ge_drawable.hpp"

namespace GE
{
  class CircleShape : public Drawable
  {
  public:
    GE3D CircleShape(f32 x, f32 y, f32 radius, Color color, Shaders shader);
    ~CircleShape() override;

    void Draw() const override;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_CIRCLE_SHAPE_HPP
