#ifndef GRAPENGINE_TRANSFORMATIONS_HPP
#define GRAPENGINE_TRANSFORMATIONS_HPP

#include "ge_vector.hpp"

#include <string>

namespace GE::Transform
{
  float GE3D Deg2Rad(float degree);

  Mat4 GE3D Translate(float xFac, float yFac, float zFac);

  Mat4 GE3D RotateX(float degrees);

  Mat4 GE3D RotateY(float degrees);

  Mat4 GE3D RotateZ(float degrees);

  Mat4 GE3D Rotate(float degrees, const Vec3& vector);

  Mat4 GE3D Scale(float xFac, float yFac, float zFac);

  Mat4 GE3D LookAt(const Vec3& eye, const Vec3& dir, const Vec3& up);

  std::tuple<Vec3, Vec3, Vec3> LookAtVector(const Vec3& eye, const Vec3& dir, const Vec3& up);

  Mat4 GE3D Perspective(float fovDegrees, float aspectRatio, float near, float far);

  Mat4 GE3D Identity();

  std::string ToString(const Mat4& mat4);
}

#endif // GRAPENGINE_TRANSFORMATIONS_HPP
