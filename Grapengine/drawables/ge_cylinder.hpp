#ifndef GRAPENGINE_CYLINDER_HPP
#define GRAPENGINE_CYLINDER_HPP

#include "drawables/ge_color.hpp"
#include "drawables/ge_drawable.hpp"
#include "drawables/ge_drawing_object.hpp"

#include <math/ge_vector.hpp>

namespace GE
{
  class Texture2D;

  class Cylinder : public Drawable
  {
  public:
    static Ptr<Cylinder> Make(const Ptr<IShaderProgram>& shader,
                              const Vec3& basePoint,
                              f32 radius,
                              const Vec3& direction,
                              f32 height,
                              Color color,
                              const Ptr<Texture2D>& texture2D);

    Cylinder(const Ptr<IShaderProgram>& shader,
             const Vec3& basePoint,
             f32 radius,
             const Vec3& direction,
             f32 height,
             Color color,
             Ptr<Texture2D> texture2D);
    ~Cylinder() override;

    void Draw() const override;

  private:
    Color m_color{ 0 };
    Ptr<DrawingObject> m_draw_primitive;
    Ptr<IShaderProgram> m_shader;
    Ptr<Texture2D> m_texture;
  };
}

#endif // GRAPENGINE_CYLINDER_HPP
