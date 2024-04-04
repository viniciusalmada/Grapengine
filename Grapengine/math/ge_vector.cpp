#include "math/ge_vector.hpp"

#include <math/ge_arithmetic.hpp>

using namespace GE;

Vec2 Vec2::operator-(const Vec2& other) const noexcept
{
  return { this->x - other.x, this->y - other.y };
}
Vec2 Vec2::operator+(const Vec2& other) const noexcept
{
  return { this->x + other.x, this->y + other.y };
}

Vec2 Vec2::operator*(f32 fac) const
{
  return Vec2{ x * fac, y * fac };
}

f32 Vec2::Length() const noexcept
{
  return std::sqrt(x * x + y * y);
}

f32 Vec2::Dot(Vec2 other) const noexcept
{
  const auto& [x1, y1] = *this;
  const auto& [x2, y2] = other;
  return x1 * x2 + y1 * y2;
}
bool Vec2::operator==(const Vec2& rhs) const
{
  return std::abs(x - rhs.x) < std::numeric_limits<f32>::epsilon() &&
         std::abs(y - rhs.y) < std::numeric_limits<f32>::epsilon();
}

bool Vec2::operator!=(const Vec2& rhs) const
{
  return !(rhs == *this);
}

Vec3 Vec3::operator+(const Vec3& other) const
{
  return { x + other.x, y + other.y, z + other.z };
}

Vec3 Vec3::operator-(const Vec3& other) const
{
  return { x - other.x, y - other.y, z - other.z };
}

Vec3& Vec3::operator-()
{
  x = -x;
  y = -y;
  z = -z;
  return *this;
}
Vec3 Vec3::operator*(const f32 fac) const
{
  return { x * fac, y * fac, z * fac };
}

Vec3& Vec3::operator+=(const Vec3& other)
{
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  return *this;
}

Vec3 Vec3::Normalize() const
{
  auto norm = std::sqrt(x * x + y * y + z * z);
  return { x / norm, y / norm, z / norm };
}

Vec3 Vec3::Cross(const Vec3& other) const
{
  const auto& [x1, y1, z1] = *this;
  const auto& [x2, y2, z2] = other;

  // clang-format off
  return {
    y1 * z2 - y2 * z1,
    x2 * z1 - x1 * z2,
    x1 * y2 - x2 * y1
  };
  // clang-format on
}

f32 Vec3::Dot(const Vec3& other) const
{
  const auto& [x1, y1, z1] = *this;
  const auto& [x2, y2, z2] = other;
  return x1 * x2 + y1 * y2 + z1 * z2;
}

f32 Vec3::Distance(const Vec3& other) const
{
  Vec3 diff = *this - other;
  return diff.Length();
}

f32 Vec3::Length() const
{
  return std::sqrt(x * x + y * y + z * z);
}

Mat4::Mat4() : Mat4({ 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 }) {}

Mat4::Mat4(const std::array<f32, 4>& row0,
           const std::array<f32, 4>& row1,
           const std::array<f32, 4>& row2,
           const std::array<f32, 4>& row3)
{
  for (u32 i = 0; i < 4; ++i)
  {
    data[i][0] = row0[i];
    data[i][1] = row1[i];
    data[i][2] = row2[i];
    data[i][3] = row3[i];
  }
}

Mat4 Mat4::operator*(const Mat4& other) const
{
  auto prod = [m1 = *this, m2 = other](u32 r, unsigned c)
  {
    // clang-format off
    return m1(r, 0) * m2(0, c) +
           m1(r, 1) * m2(1, c) +
           m1(r, 2) * m2(2, c) +
           m1(r, 3) * m2(3, c);
    // clang-format on
  };

  Mat4 res;
  for (u32 row = 0; row < 4; ++row)
  {
    for (u32 col = 0; col < 4; ++col)
    {
      res(row, col) = prod(row, col);
    }
  }

  return res;
}

f32& Mat4::operator()(u32 row, u32 col)
{
  return data[col][row];
}

const f32& Mat4::operator()(u32 row, u32 col) const
{
  return data[col][row];
}

const f32* Mat4::ValuePtr() const
{
  return data.data()->data();
}

bool Mat4::operator==(const Mat4& other) const
{
  for (u32 i = 0; i < 4; ++i)
  {
    for (u32 j = 0; j < 4; ++j)
    {
      if (!Arithmetic::IsEqual(other(i, j), this->operator()(i, j)))
        return false;
    }
  }
  return true;
}

bool IVec3::operator<(const IVec3& other) const
{
  if (x < other.x)
    return true;

  if (x == other.x)
  {
    if (y < other.y)
      return true;

    if (y == other.y)
    {
      if (z < other.z)
        return true;
    }
  }
  return false;
}
