#ifndef GRAPHICENGINE3D_GE_RECT_SHAPE_HPP
#define GRAPHICENGINE3D_GE_RECT_SHAPE_HPP

#include "ge_drawable.hpp"

class RectShape : public Drawable
{
public:
  GE3D RectShape(float x, float y, float w, float h);
  ~RectShape() override;

  void Draw() const override;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHICENGINE3D_GE_RECT_SHAPE_HPP
