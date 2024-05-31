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

std::ostream& GE::operator<<(std::ostream& os, const Vec2& vec)
{
#if __cpp_lib_format
  os << std::format("{:1.2f},{:1.2f}", vec.x, vec.y);
#else
  os << std::setprecision(2) << vec.x << "," << vec.y;
#endif
  return os;
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
  const Vec3 diff = *this - other;
  return diff.Length();
}

f32 Vec3::Length() const
{
  return std::sqrt(x * x + y * y + z * z);
}
std::ostream& GE::operator<<(std::ostream& os, const Vec3& vec3)
{
#if __cpp_lib_format
  os << std::format("{:1.2f},{:1.2f},{:1.2f}", vec3.x, vec3.y, vec3.z);
#else
  os << std::setprecision(2) << vec3.x << "," << vec3.y << "," << vec3.z;
#endif
  return os;
}

Mat4::Mat4() : Mat4({ { 1, 0, 0, 0 } }, { { 0, 1, 0, 0 } }, { { 0, 0, 1, 0 } }, { { 0, 0, 0, 1 } })
{
}

Mat4::Mat4(const std::array<f32, 4>& row0,
           const std::array<f32, 4>& row1,
           const std::array<f32, 4>& row2,
           const std::array<f32, 4>& row3)
{
  for (u32 i = 0; i < 4; ++i)
  {
    data.at(i).at(0) = row0.at(i);
    data.at(i).at(1) = row1.at(i);
    data.at(i).at(2) = row2.at(i);
    data.at(i).at(3) = row3.at(i);
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
  return data.at(col).at(row);
}

const f32& Mat4::operator()(u32 row, u32 col) const
{
  return data.at(col).at(row);
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

Vec4 Mat4::operator*(const Vec4& other) const
{
  Vec4 res{ 0, 0, 0, 0 };
  const Mat4& m = *this;
  res.x0 = m(0, 0) * other.x0 + m(0, 1) * other.x1 + m(0, 2) * other.x2 + m(0, 3) * other.x3;
  res.x1 = m(1, 0) * other.x0 + m(1, 1) * other.x1 + m(1, 2) * other.x2 + m(1, 3) * other.x3;
  res.x2 = m(2, 0) * other.x0 + m(2, 1) * other.x1 + m(2, 2) * other.x2 + m(2, 3) * other.x3;
  res.x3 = m(3, 0) * other.x0 + m(3, 1) * other.x1 + m(3, 2) * other.x2 + m(3, 3) * other.x3;
  return res;
}

Vec3 Mat4::operator*(const Vec3& other) const
{
  Vec4 vec{ other };
  auto res = this->operator*(vec);
  return { res.x0, res.x1, res.x2 };
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
