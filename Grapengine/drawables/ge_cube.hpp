#ifndef GRAPENGINE_CUBE_HPP
#define GRAPENGINE_CUBE_HPP

#include "ge_color.hpp"
#include "ge_drawable.hpp"
#include "ge_drawing_object.hpp"
#include "math/ge_vector.hpp"
#include "renderer/ge_ishader_program.hpp"
#include "renderer/ge_texture_2d.hpp"
#include "renderer/ge_vertex_array.hpp"

namespace GE
{
  class Cube : public Drawable
  {
  public:
    static Ref<Cube> Make(Color color, const Ref<IShaderProgram>&, Ref<Texture2D> texture);

    Cube(Color color, const Ref<IShaderProgram>&, Ref<Texture2D> texture);

    ~Cube() override;

    void SetColor(Color color);
    void Draw() const override;

    void SetScale(f32 x, f32 y, f32 z) const;
    void SetTranslate(f32 x, f32 y, f32 z) const;
    void SetTranslate(Vec3 xyz) const;

    [[nodiscard]] Ref<DrawingObject> GetVAO() const;
    [[nodiscard]] Mat4 GetModelMatrix() const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_CUBE_HPP
