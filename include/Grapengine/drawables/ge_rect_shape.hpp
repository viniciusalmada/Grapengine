#ifndef GRAPENGINE_RECT_SHAPE_HPP
#define GRAPENGINE_RECT_SHAPE_HPP

#include "ge_color.hpp"
#include "ge_drawable.hpp"
#include "math/ge_vector.hpp"
namespace GE
{
  class RectShape : public Drawable
  {
  public:
    GE3D RectShape(float x, float y, float w, float h, Color color, Shaders shader);
    GE3D RectShape(Vec3 botLeft,
                   Vec3 botRight,
                   Vec3 topRight,
                   Vec3 topLeft,
                   Color color,
                   Shaders shader,
                   std::string path = "");
    ~RectShape() override;

    void Draw() const override;

    [[nodiscard]] GE3D Vec2 GetPosition() const;
    GE3D void SetPosition(float x, float y) const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}
#endif // GRAPENGINE_RECT_SHAPE_HPP
