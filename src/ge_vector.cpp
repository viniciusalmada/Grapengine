#include "ge_vector.hpp"

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

float Vec3::Dot(const Vec3& other) const
{
  const auto& [x1, y1, z1] = *this;
  const auto& [x2, y2, z2] = other;
  return x1 * x2 + y1 * y2 + z1 * z2;
}

Mat4::Mat4() : Mat4({ 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 }) {}

Mat4::Mat4(const std::array<float, 4>& row0,
           const std::array<float, 4>& row1,
           const std::array<float, 4>& row2,
           const std::array<float, 4>& row3)
{
  for (int i = 0; i < 4; ++i)
  {
    data[0][i] = row0[i];
    data[1][i] = row1[i];
    data[2][i] = row2[i];
    data[3][i] = row3[i];
  }
}

Mat4 Mat4::operator*(const Mat4& other) const
{
  auto prod = [m1 = *this, m2 = other](unsigned int r, unsigned c)
  {
    // clang-format off
    return m1(r, 0) * m2(0, c) +
           m1(r, 1) * m2(1, c) +
           m1(r, 2) * m2(2, c) +
           m1(r, 3) * m2(3, c);
    // clang-format on
  };

  Mat4 res;
  for (int row = 0; row < 4; ++row)
  {
    for (int col = 0; col < 4; ++col)
    {
      res(row, col) = prod(row, col);
    }
  }

  return res;
}

float& Mat4::operator()(unsigned int row, unsigned int col)
{
  return data[col][row];
}

const float& Mat4::operator()(unsigned int row, unsigned int col) const
{
  return data[col][row];
}

const float* Mat4::ValuePtr() const
{
  return data.data()->data();
}
