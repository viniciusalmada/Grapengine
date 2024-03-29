#ifndef GRAPENGINE_CUBE_HPP
#define GRAPENGINE_CUBE_HPP

#include "ge_color.hpp"
#include "ge_drawable.hpp"
#include "math/ge_vector.hpp"
#include "renderer/ge_ishader_program.hpp"
#include "renderer/ge_texture_2d.hpp"

namespace GE
{
  class Cube : public Drawable
  {
  public:
    static Ref<Cube> Make(Color color, const Ref<IShaderProgram>&, Ref<Texture2D> texture);

    GE3D Cube(Color color, const Ref<IShaderProgram>&, Ref<Texture2D> texture);

    ~Cube() override;

    void Draw() const override;

    void SetScale(f32 x, f32 y, f32 z) const;
    void SetTranslate(f32 x, f32 y, f32 z) const;
    void SetTranslate(Vec3 xyz) const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_CUBE_HPP
