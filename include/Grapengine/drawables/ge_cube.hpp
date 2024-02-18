#ifndef GRAPENGINE_CUBE_HPP
#define GRAPENGINE_CUBE_HPP

#include "ge_color.hpp"
#include "ge_drawable.hpp"
#include "math/ge_vector.hpp"

namespace GE
{
  class Texture2D;

  class Cube : public Drawable
  {
  public:
    GE3D Cube(Color color, Shaders shader, Ref<Texture2D> texture);
    ~Cube() override;

    void Draw() const override;

    void SetScale(f32 x, f32 y, f32 z) const;
    void SetTranslate(f32 x, f32 y, f32 z) const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_CUBE_HPP
