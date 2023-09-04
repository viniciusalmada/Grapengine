#ifndef GRAPHICENGINE3D_GE_TRANSFORMATIONS_HPP
#define GRAPHICENGINE3D_GE_TRANSFORMATIONS_HPP

#include "ge_vector.hpp"

namespace Transform
{
  Mat4 Translate(float xFac, float yFac, float zFac);

  Mat4 RotateX(float degrees);

  Mat4 RotateY(float degrees);

  Mat4 RotateZ(float degrees);

  Mat4 Scale(float xFac, float yFac, float zFac);

  Mat4 LookAt(const Vec3& eye, const Vec3& dir, const Vec3& up);

  Mat4 Perspective(float fovDegrees, float aspectRatio, float near, float far);

  Mat4 Identity();
}

#endif // GRAPHICENGINE3D_GE_TRANSFORMATIONS_HPP
