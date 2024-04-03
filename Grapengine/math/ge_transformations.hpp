#ifndef GRAPENGINE_TRANSFORMATIONS_HPP
#define GRAPENGINE_TRANSFORMATIONS_HPP

#include "ge_vector.hpp"

#include <string>

namespace GE::Transform
{
  f32 GE3D Deg2Rad(f32 degree);
  f32 GE3D Rad2Deg(f32 rad);

  Mat4 GE3D Translate(f32 xFac, f32 yFac, f32 zFac);

  Mat4 GE3D RotateX(f32 degrees);

  Mat4 GE3D RotateY(f32 degrees);

  Mat4 GE3D RotateZ(f32 degrees);

  Mat4 GE3D Rotate(f32 degrees, const Vec3& vector);

  Mat4 GE3D Scale(f32 xFac, f32 yFac, f32 zFac);

  Mat4 GE3D LookAt(const Vec3& eye, const Vec3& dir, const Vec3& up);

  std::tuple<Vec3, Vec3, Vec3> LookAtVector(const Vec3& eye, const Vec3& dir, const Vec3& up);

  Mat4 GE3D Perspective(f32 fovDegrees, f32 aspectRatio, f32 near, f32 far);

  Mat4 GE3D Identity();

  std::string ToString(const Mat4& mat4);
}

#endif // GRAPENGINE_TRANSFORMATIONS_HPP
