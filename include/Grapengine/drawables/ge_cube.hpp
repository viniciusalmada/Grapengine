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
    GE3D Cube(float x, float y, float z, Color color, Shaders shader, Ref<Texture2D> texture);
    ~Cube() override;

    void Draw() const override;

    void SetScale(float x, float y, float z) const;
    void SetTranslate(float x, float y, float z) const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_CUBE_HPP
