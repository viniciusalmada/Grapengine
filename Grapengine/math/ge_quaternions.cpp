#include "math/ge_quaternions.hpp"

using namespace GE;

Quaternion Quaternion::IDENTITY{ 1, 0, 0, 0 };

Quaternion::Quaternion(f32 angle, Vec3 axis)
{
  Vec3 unit = axis.Normalize();
  m_w = std::cos(Transform::Deg2Rad(angle / 2.0f));
  m_x = std::sin(Transform::Deg2Rad(angle / 2.0f)) * unit.x;
  m_y = std::sin(Transform::Deg2Rad(angle / 2.0f)) * unit.y;
  m_z = std::sin(Transform::Deg2Rad(angle / 2.0f)) * unit.z;
}

Quaternion::Quaternion(f32 w, f32 x, f32 y, f32 z)
{
  m_w = w;
  m_x = x;
  m_y = y;
  m_z = z;
}

Quaternion::Quaternion(const Quaternion& other) = default;

Quaternion Quaternion::Conjugate() const
{
  return { m_w, -m_x, -m_y, -m_z };
}

Quaternion Quaternion::operator*(const Quaternion& other) const
{
  const auto& a1 = m_w;
  const auto& b1 = m_x;
  const auto& c1 = m_y;
  const auto& d1 = m_z;
  const auto& a2 = other.m_w;
  const auto& b2 = other.m_x;
  const auto& c2 = other.m_y;
  const auto& d2 = other.m_z;
  f32 w_result = a1 * a2 - b1 * b2 - c1 * c2 - d1 * d2;
  f32 x_result = a1 * b2 + b1 * a2 + c1 * d2 - d1 * c2;
  f32 y_result = a1 * c2 - b1 * d2 + c1 * a2 + d1 * b2;
  f32 z_result = a1 * d2 + b1 * c2 - c1 * b2 + d1 * a2;
  return { w_result, x_result, y_result, z_result };
}
f32 Quaternion::Length() const noexcept
{
  return std::sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
}

Vec3 Quaternion::RotateVector(Vec3 A) const
{
  Quaternion q_a{ 0, A.x, A.y, A.z };
  const Quaternion& Q = *this;
  Quaternion result = Q * q_a * Q.Conjugate();
  return result.GetVec();
}

Vec3 Quaternion::GetVec() const noexcept
{
  return Vec3(m_x, m_y, m_z);
}

Quaternion& Quaternion::operator=(const Quaternion& other) = default;

Quaternion::~Quaternion() = default;
