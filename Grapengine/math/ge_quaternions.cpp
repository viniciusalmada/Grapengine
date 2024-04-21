#include "math/ge_quaternions.hpp"

using namespace GE;

namespace
{
  constexpr auto ANGLE_DIVISOR = 2.0f;
}

Quaternion::Quaternion(f32 angle, Vec3 axis) :
    m_w(std::cos(Transform::Deg2Rad(angle / ANGLE_DIVISOR)))
{
  const Vec3 unit = axis.Normalize();

  m_x = std::sin(Transform::Deg2Rad(angle / ANGLE_DIVISOR)) * unit.x;
  m_y = std::sin(Transform::Deg2Rad(angle / ANGLE_DIVISOR)) * unit.y;
  m_z = std::sin(Transform::Deg2Rad(angle / ANGLE_DIVISOR)) * unit.z;
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
  const f32 w_result = a1 * a2 - b1 * b2 - c1 * c2 - d1 * d2;
  const f32 x_result = a1 * b2 + b1 * a2 + c1 * d2 - d1 * c2;
  const f32 y_result = a1 * c2 - b1 * d2 + c1 * a2 + d1 * b2;
  const f32 z_result = a1 * d2 + b1 * c2 - c1 * b2 + d1 * a2;
  return { w_result, x_result, y_result, z_result };
}
f32 Quaternion::Length() const noexcept
{
  return std::sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
}

Vec3 Quaternion::RotateVector(Vec3 A) const
{
  const Quaternion q_a{ 0, A.x, A.y, A.z };
  const Quaternion& Q = *this;
  const Quaternion result = Q * q_a * Q.Conjugate();
  return result.GetVec();
}

Vec3 Quaternion::GetVec() const noexcept
{
  return Vec3{ m_x, m_y, m_z };
}

Quaternion& Quaternion::operator=(const Quaternion& other) = default;
