#include "ge_vector.hpp"

Vec3 Normalize(const Vec3& v)
{
  const auto& [x, y, z] = v;
  auto norm = std::sqrt(x * x + y * y + z * z);
  return std::make_tuple(x / norm, y / norm, z / norm);
}

Vec3 operator-(const Vec3& v1, const Vec3& v2)
{
  const auto& [x1, y1, z1] = v1;
  const auto& [x2, y2, z2] = v2;

  return std::make_tuple(x1 - x2, y1 - y2, z1 - z2);
}

Vec3 Cross(const Vec3& v1, const Vec3& v2)
{
  const auto& [x1, y1, z1] = v1;
  const auto& [x2, y2, z2] = v2;

  // clang-format off
  return std::make_tuple(
    y1 * z2 - y2 * z1,
    x2 * z1 - x1 * z2,
    x1 * y2 - x2 * y1
    );
  // clang-format on
}
float Dot(const Vec3& v1, const Vec3& v2)
{
  const auto& [x1, y1, z1] = v1;
  const auto& [x2, y2, z2] = v2;
  return x1 * x2 + y1 * y2 + z1 * z2;
}

Vec3& operator-(Vec3& v)
{
  auto& [x1, y1, z1] = v;
  x1 = -x1;
  y1 = -y1;
  z1 = -z1;
  return v;
}
