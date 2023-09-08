#ifndef GRAPHICENGINE3D_GE_TRANSFORMATIONS_HPP
#define GRAPHICENGINE3D_GE_TRANSFORMATIONS_HPP

#include "ge_vector.hpp"

namespace Transform
{
  float GE3D Deg2Rad(float degree);

  Mat4 GE3D Translate(float xFac, float yFac, float zFac);

  Mat4 GE3D RotateX(float degrees);

  Mat4 GE3D RotateY(float degrees);

  Mat4 GE3D RotateZ(float degrees);

  Mat4 GE3D Scale(float xFac, float yFac, float zFac);

  Mat4 GE3D LookAt(const Vec3& eye, const Vec3& dir, const Vec3& up);

  Mat4 GE3D Perspective(float fovDegrees, float aspectRatio, float near, float far);

  Mat4 GE3D Identity();
}

#endif // GRAPHICENGINE3D_GE_TRANSFORMATIONS_HPP
