#ifndef GRAPENGINE_TRANSFORMATIONS_HPP
#define GRAPENGINE_TRANSFORMATIONS_HPP

#include "ge_vector.hpp"

#include <string>

namespace GE::Transform
{
  constexpr f32 FRUSTUM_NEAR = 0.1f;
  constexpr f32 FRUSTUM_FAR = 1000.0f;
  constexpr Vec3 UP_VECTOR{ 0, 1, 0 };

  f32 Deg2Rad(f32 degree);
  f32 Rad2Deg(f32 rad);

  Mat4 Translate(const Vec3& fac);
  Mat4 Translate(f32 xFac, f32 yFac, f32 zFac);

  Mat4 RotateX(f32 degrees);

  Mat4 RotateY(f32 degrees);

  Mat4 RotateZ(f32 degrees);

  Mat4 Rotate(f32 degrees, const Vec3& vector);

  Mat4 Scale(f32 xFac, f32 yFac, f32 zFac);
  Mat4 Scale(const Vec3& fac);

  Mat4 LookAt(const Vec3& eye, const Vec3& target, const Vec3& up = UP_VECTOR);

  std::tuple<Vec3, Vec3, Vec3> LookAtVector(const Vec3& eye, const Vec3& target, const Vec3& up);

  Mat4 Perspective(f32 fovDegrees, f32 aspectRatio, f32 near = FRUSTUM_NEAR, f32 far = FRUSTUM_FAR);

  Mat4
  Ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near = FRUSTUM_NEAR, f32 far = FRUSTUM_FAR);

  Mat4 Identity();
}

#endif // GRAPENGINE_TRANSFORMATIONS_HPP
