//
// Created by vinic on 11-Aug-23.
//

#include "math/ge_transformations.hpp"

#include <math/ge_vector.hpp>

using namespace GE;

namespace
{
  constexpr auto STRAIGHT_ANGLE = 180.0f;
}

f32 Transform::Deg2Rad(f32 deg)
{
  return deg * (std::numbers::pi_v<decltype(deg)> / STRAIGHT_ANGLE);
}

f32 Transform::Rad2Deg(f32 rad)
{
  return rad * (STRAIGHT_ANGLE / std::numbers::pi_v<decltype(rad)>);
}

Mat4 Transform::Translate(f32 xFac, f32 yFac, f32 zFac)
{
  return Mat4{
    { { 1, 0, 0, xFac } },
    { { 0, 1, 0, yFac } },
    { { 0, 0, 1, zFac } },
    { { 0, 0, 0, 1 } },
  };
}

Mat4 Transform::RotateX(f32 degrees)
{
  auto c = std::cos(Deg2Rad(degrees));
  auto s = std::sin(Deg2Rad(degrees));
  return Mat4{
    { { 1, 0, 0, 0 } },
    { { 0, c, -s, 0 } },
    { { 0, s, c, 0 } },
    { { 0, 0, 0, 1 } },
  };
}

Mat4 Transform::RotateY(f32 degrees)
{
  auto c = std::cos(Deg2Rad(degrees));
  auto s = std::sin(Deg2Rad(degrees));
  return Mat4{ { { c, 0, s, 0 } }, //
               { { 0, 1, 0, 0 } },
               { { -s, 0, c, 0 } },
               { { 0, 0, 0, 1 } } };
}

Mat4 Transform::RotateZ(f32 degrees)
{
  auto c = std::cos(Deg2Rad(degrees));
  auto s = std::sin(Deg2Rad(degrees));
  return Mat4{
    { { c, -s, 0, 0 } },
    { { s, c, 0, 0 } },
    { { 0, 0, 1, 0 } },
    { { 0, 0, 0, 1 } },
  };
}

Mat4 Transform::Rotate(f32 degrees, const Vec3& vector)
{
  Mat4 res = Identity();
  const Vec3 norm = vector.Normalize();
  const auto& vx = norm.x;
  const auto& vy = norm.y;
  const auto& vz = norm.z;
  const auto& ct = std::cos(Deg2Rad(degrees));
  const auto& st = std::sin(Deg2Rad(degrees));

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

Mat4 Transform::Scale(f32 xFac, f32 yFac, f32 zFac)
{
  return Mat4{
    { { xFac, 0, 0, 0 } },
    { { 0, yFac, 0, 0 } },
    { { 0, 0, zFac, 0 } },
    { { 0, 0, 0, 1 } },
  };
}

// NOLINTBEGIN(bugprone-easily-swappable-parameters)
std::tuple<Vec3, Vec3, Vec3>
Transform::LookAtVector(const Vec3& eye, const Vec3& target, const Vec3& up)
{
  Vec3 view = (target - eye).Normalize();
  const Vec3 z_eye = -view;
  const Vec3 x_eye = (up.Cross(z_eye)).Normalize();
  const Vec3 y_eye = z_eye.Cross(x_eye);
  return { x_eye, y_eye, z_eye };
}
// NOLINTEND(bugprone-easily-swappable-parameters)

Mat4 Transform::LookAt(const Vec3& eye, const Vec3& target, const Vec3& up)
{
  const auto& [x_eye, y_eye, z_eye] = LookAtVector(eye, target, up);

  const auto& [Rx, Ry, Rz] = x_eye;
  const auto& [Ux, Uy, Uz] = y_eye;
  const auto& [Dx, Dy, Dz] = z_eye;

  const Mat4 m1{
    { { Rx, Ry, Rz, 0 } },
    { { Ux, Uy, Uz, 0 } },
    { { Dx, Dy, Dz, 0 } },
    { { 0, 0, 0, 1 } },
  };

  const Mat4 m2{
    { { 1, 0, 0, -eye.x } },
    { { 0, 1, 0, -eye.y } },
    { { 0, 0, 1, -eye.z } },
    { { 0, 0, 0, 1 } },
  };

  auto res = m1 * m2;

  return res;
}

Mat4 Transform::Identity()
{
  return Mat4{
    { { 1, 0, 0, 0 } },
    { { 0, 1, 0, 0 } },
    { { 0, 0, 1, 0 } },
    { { 0, 0, 0, 1 } },
  };
}

// NOLINTBEGIN(bugprone-easily-swappable-parameters)
Mat4 Transform::Perspective(f32 fovDegrees, f32 aspectRatio, f32 near, f32 far)
{
  // NOLINTNEXTLINE(*-avoid-magic-numbers,*-magic-numbers)
  auto tan_half_fov = std::tan(Deg2Rad(fovDegrees) / 2.0f);

  Mat4 res{
    { { 1 / (aspectRatio * tan_half_fov), 0, 0, 0 } },
    { { 0, 1 / (tan_half_fov), 0, 0 } },
    { { 0, 0, -(far + near) / (far - near), -(2 * far * near) / (far - near) } },
    { { 0, 0, -1, 0 } },
  };

  return res;
}
// NOLINTEND(bugprone-easily-swappable-parameters)
