//
// Created by vinic on 11-Aug-23.
//

#include "ge_transformations.hpp"

inline auto radians(float deg)
{
  return deg * (std::numbers::pi_v<decltype(deg)> / 180.0f);
}

Mat4 Transform::Translate(float xFac, float yFac, float zFac)
{
  return Mat4{
    { 1, 0, 0, xFac },
    { 0, 1, 0, yFac },
    { 0, 0, 1, zFac },
    { 0, 0, 0, 1 },
  };
}

Mat4 Transform::RotateX(float degrees)
{
  auto c = std::cosf(radians(degrees));
  auto s = std::sinf(radians(degrees));
  return Mat4{
    { 1, 0, 0, 0 },
    { 0, c, s, 0 },
    { 0, -s, c, 0 },
    { 0, 0, 0, 1 },
  };
}

Mat4 Transform::RotateY(float degrees)
{
  auto c = std::cosf(radians(degrees));
  auto s = std::sinf(radians(degrees));
  return Mat4{ { c, 0, s, 0 }, { 0, 1, 0, 0 }, { -s, 0, c, 0 }, { 0, 0, 0, 1 } };
}

Mat4 Transform::RotateZ(float degrees)
{
  auto c = std::cosf(radians(degrees));
  auto s = std::sinf(radians(degrees));
  return Mat4{
    { c, s, 0, 0 },
    { -s, c, 0, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 },
  };
}

Mat4 Transform::Scale(float xFac, float yFac, float zFac)
{
  return Mat4{
    { xFac, 0, 0, 0 },
    { 0, yFac, 0, 0 },
    { 0, 0, zFac, 0 },
    { 0, 0, 0, 1 },
  };
}

Mat4 Transform::LookAt(const Vec3& eye, const Vec3& target, const Vec3& up)
{
  Vec3 view = (eye - target).Normalize();
  Vec3 z_eye = -view;
  Vec3 x_eye = (up.Cross(z_eye)).Normalize();
  Vec3 y_eye = z_eye.Cross(x_eye);

  const auto& [Rx, Ry, Rz] = x_eye;
  const auto& [Ux, Uy, Uz] = y_eye;
  const auto& [Dx, Dy, Dz] = z_eye;

  Mat4 m1{
    { Rx, Ry, Rz, 0 },
    { Ux, Uy, Uz, 0 },
    { Dx, Dy, Dz, 0 },
    { 0, 0, 0, 1 },
  };

  Mat4 m2{
    { 1, 0, 0, -eye.x },
    { 0, 1, 0, -eye.y },
    { 0, 0, 1, -eye.z },
    { 0, 0, 0, 1 },
  };

  return m1 * m2;
}

Mat4 Transform::Identity()
{
  return Mat4{
    { 1, 0, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 },
  };
}

Mat4 Transform::Perspective(float fovDegrees, float aspectRatio, float near, float far)
{
  auto tan_half_fov = std::tanf(radians(fovDegrees) / 2.0f);

  Mat4 res{
    { 1 / (aspectRatio * tan_half_fov), 0, 0, 0 },
    { 0, 1 / (tan_half_fov), 0, 0 },
    { 0, 0, -(far + near) / (far - near), -1 },
    { 0, 0, (2 * far * near) / (far - near), 0 },
  };

  return res;
}
