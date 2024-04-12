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
    static Ref<Cylinder> Make(const Ref<IShaderProgram>& shader,
                              f32 radius,
                              const Vec3& basePoint,
                              const Vec3& direction,
                              f32 height,
                              Color color,
                              const Ref<Texture2D>& texture2D);

    Cylinder(const Ref<IShaderProgram>& shader,
             f32 radius,
             const Vec3& basePoint,
             const Vec3& direction,
             f32 height,
             Color color,
             Ref<Texture2D> texture2D);
    ~Cylinder() override;

    void Draw() const override;

  private:
    Color m_color{ 0 };
    Ref<DrawingObject> m_draw_primitive;
    Ref<IShaderProgram> m_shader;
    Ref<Texture2D> m_texture;
  };
}

#endif // GRAPENGINE_CYLINDER_HPP
