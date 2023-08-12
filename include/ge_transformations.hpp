#ifndef GRAPHICENGINE3D_GE_TRANSFORMATIONS_HPP
#define GRAPHICENGINE3D_GE_TRANSFORMATIONS_HPP

#include "ge_vector.hpp"

namespace Transform
{
  Mat4<float> Translate(float xFac, float yFac, float zFac);

  Mat4<float> RotateX(float degrees);

  Mat4<float> RotateY(float degrees);

  Mat4<float> RotateZ(float degrees);
};

#endif // GRAPHICENGINE3D_GE_TRANSFORMATIONS_HPP
