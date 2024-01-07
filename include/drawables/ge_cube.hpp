#ifndef GRAPHICENGINE3D_GE_CUBE_HPP
#define GRAPHICENGINE3D_GE_CUBE_HPP

#include "ge_color.hpp"
#include "ge_drawable.hpp"
#include "math/ge_vector.hpp"

class Cube : public Drawable
{
public:
  GE3D Cube(float x, float y, float z, Shaders shader);
  ~Cube() override;

  void Draw() const override;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHICENGINE3D_GE_CUBE_HPP
