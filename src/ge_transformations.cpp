//
// Created by vinic on 11-Aug-23.
//

#include "math/ge_transformations.hpp"

#include <math/ge_vector.hpp>

inline float Transform::Deg2Rad(float deg)
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
  auto c = std::cosf(Deg2Rad(degrees));
  auto s = std::sinf(Deg2Rad(degrees));
  return Mat4{
    { 1, 0, 0, 0 },
    { 0, c, -s, 0 },
    { 0, s, c, 0 },
    { 0, 0, 0, 1 },
  };
}

Mat4 Transform::RotateY(float degrees)
{
  auto c = std::cosf(Deg2Rad(degrees));
  auto s = std::sinf(Deg2Rad(degrees));
  return Mat4{ { c, 0, s, 0 }, { 0, 1, 0, 0 }, { -s, 0, c, 0 }, { 0, 0, 0, 1 } };
}

Mat4 Transform::RotateZ(float degrees)
{
  auto c = std::cosf(Deg2Rad(degrees));
  auto s = std::sinf(Deg2Rad(degrees));
  return Mat4{
    { c, -s, 0, 0 },
    { s, c, 0, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 },
  };
}

Mat4 Transform::Rotate(float degrees, const Vec3& vector)
{
  Mat4 res = Identity();
  Vec3 norm = vector.Normalize();
  const auto& vx = norm.x;
  const auto& vy = norm.y;
  const auto& vz = norm.z;
  const auto& ct = std::cosf(Deg2Rad(degrees));
  const auto& st = std::sinf(Deg2Rad(degrees));

  res(0, 0) = vx * vx + ct * (1 - vx * vx);
  res(0, 1) = vx * vy * (1 - ct) - vz * st;
  res(0, 2) = vz * vx * (1 - ct) + vy * st;

  res(1, 0) = vx * vy * (1 - ct) + vz * st;
  res(1, 1) = vy * vy + ct * (1 - vy * vy);
  res(1, 2) = vy * vz * (1 - ct) - vx * st;

  res(2, 0) = vx * vz * (1 - ct) - vy * st;
  res(2, 1) = vy * vz * (1 - ct) + vx * st;
  res(2, 2) = vz * vz + ct * (1 - vz * vz);

  return res;
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
  Vec3 view = (target - eye).Normalize();
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
  auto tan_half_fov = std::tanf(Deg2Rad(fovDegrees) / 2.0f);

  Mat4 res{
    { 1 / (aspectRatio * tan_half_fov), 0, 0, 0 },
    { 0, 1 / (tan_half_fov), 0, 0 },
    { 0, 0, -(far + near) / (far - near), -(2 * far * near) / (far - near) },
    { 0, 0, -1, 0 },
  };

  return res;
}

std::string Transform::ToString(const Mat4& mat4)
{
  std::string str{ "mat4x4(" };
  i32 count = 0;
  for (i32 i = 0; i < 16; ++i)
  {
    if (count == 0)
      str.append("(");
    str.append(std::to_string(mat4.ValuePtr()[i]));
    if (count < 3)
      str.append(", ");
    count++;
    if (count == 4)
    {
      str.append("), ");
      count = 0;
    }
  }
  str.append(")");
  return str;
}
