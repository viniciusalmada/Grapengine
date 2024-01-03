#ifndef GRAPHICENGINE3D_GE_RECT_SHAPE_HPP
#define GRAPHICENGINE3D_GE_RECT_SHAPE_HPP

#include "ge_color.hpp"
#include "ge_drawable.hpp"
#include "math/ge_vector.hpp"

class RectShape : public Drawable
{
public:
  GE3D RectShape(float x, float y, float w, float h, Color color);
  ~RectShape() override;

  void Draw() const override;

  [[nodiscard]] GE3D Vec2 GetPosition() const;
  GE3D void SetPosition(float x, float y) const;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHICENGINE3D_GE_RECT_SHAPE_HPP
