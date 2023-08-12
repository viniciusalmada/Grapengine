//
// Created by vinic on 11-Aug-23.
//

#include "ge_transformations.hpp"

inline auto radians(float deg)
{
  return deg * (std::numbers::pi_v<decltype(deg)> / 180.0f);
}

Mat4<float> Transform::Translate(float xFac, float yFac, float zFac)
{
  return Mat4<float>{ {
    { 1, 0, 0, xFac },
    { 0, 1, 0, yFac },
    { 0, 0, 1, zFac },
    { 0, 0, 0, 1 },
  } };
}

Mat4<float> Transform::RotateX(float degrees)
{
  auto c = std::cosf(radians(degrees));
  auto s = std::sinf(radians(degrees));
  return Mat4<float>{ {
    { 1, 0, 0, 0 },
    { 0, c, s, 0 },
    { 0, -s, c, 0 },
    { 0, 0, 0, 1 },
  } };
}

Mat4<float> Transform::RotateY(float degrees)
{
  auto c = std::cosf(radians(degrees));
  auto s = std::sinf(radians(degrees));
  return Mat4<float>{ {
    { c, 0, s, 0 },
    { 0, 1, 0, 0 },
    { -s, 0, c, 0 },
    { 0, 0, 0, 1 },
  } };
}

Mat4<float> Transform::RotateZ(float degrees)
{
  auto c = std::cosf(radians(degrees));
  auto s = std::sinf(radians(degrees));
  return Mat4<float>{ {
    { c, s, 0, 0 },
    { -s, c, 0, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 },
  } };
}

Mat4<float> Transform::Scale(float xFac, float yFac, float zFac)
{
  return Mat4<float>{ {
    { xFac, 0, 0, 0 },
    { 0, yFac, 0, 0 },
    { 0, 0, zFac, 0 },
    { 0, 0, 0, 1 },
  } };
}
