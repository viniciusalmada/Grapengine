#ifndef GRAPHICENGINE3D_GE_CIRCLE_SHAPE_HPP
#define GRAPHICENGINE3D_GE_CIRCLE_SHAPE_HPP

#include "ge_color.hpp"
#include "ge_drawable.hpp"

class CircleShape : public Drawable
{
public:
  GE3D CircleShape(float x, float y, float radius, Color color);
  ~CircleShape() override;

  void Draw() const override;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHICENGINE3D_GE_CIRCLE_SHAPE_HPP
