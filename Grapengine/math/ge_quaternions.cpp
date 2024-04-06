#include "math/ge_quaternions.hpp"

using namespace GE;

Quaternion Quaternion::IDENTITY{ 1, 0, 0, 0 };

struct Quaternion::Impl
{
  f32 m_w = 0;
  f32 m_x = 0;
  f32 m_y = 0;
  f32 m_z = 0;
};

Quaternion::Quaternion(f32 angle, GE::Vec3 axis) : m_pimpl(MakeScope<Impl>())
{
  Vec3 unit = axis.Normalize();
  m_pimpl->m_w = std::cos(Transform::Deg2Rad(angle / 2.0f));
  m_pimpl->m_x = std::sin(Transform::Deg2Rad(angle / 2.0f)) * unit.x;
  m_pimpl->m_y = std::sin(Transform::Deg2Rad(angle / 2.0f)) * unit.y;
  m_pimpl->m_z = std::sin(Transform::Deg2Rad(angle / 2.0f)) * unit.z;
}

Quaternion::Quaternion(f32 w, f32 x, f32 y, f32 z) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->m_w = w;
  m_pimpl->m_x = x;
  m_pimpl->m_y = y;
  m_pimpl->m_z = z;
}

Quaternion::Quaternion(const Quaternion& other) : m_pimpl(MakeScope<Impl>(*other.m_pimpl.get())) {}

Quaternion GE::Quaternion::Conjugate() const
{
  return { m_pimpl->m_w, -m_pimpl->m_x, -m_pimpl->m_y, -m_pimpl->m_z };
}

Quaternion GE::Quaternion::operator*(const Quaternion& other) const
{
  const auto& a1 = m_pimpl->m_w;
  const auto& b1 = m_pimpl->m_x;
  const auto& c1 = m_pimpl->m_y;
  const auto& d1 = m_pimpl->m_z;
  const auto& a2 = other.m_pimpl->m_w;
  const auto& b2 = other.m_pimpl->m_x;
  const auto& c2 = other.m_pimpl->m_y;
  const auto& d2 = other.m_pimpl->m_z;
  f32 w_result = a1 * a2 - b1 * b2 - c1 * c2 - d1 * d2;
  f32 x_result = a1 * b2 + b1 * a2 + c1 * d2 - d1 * c2;
  f32 y_result = a1 * c2 - b1 * d2 + c1 * a2 + d1 * b2;
  f32 z_result = a1 * d2 + b1 * c2 - c1 * b2 + d1 * a2;
  return { w_result, x_result, y_result, z_result };
}
f32 GE::Quaternion::Length() const noexcept
{
  return std::sqrt(m_pimpl->m_w * m_pimpl->m_w + m_pimpl->m_x * m_pimpl->m_x +
                   m_pimpl->m_y * m_pimpl->m_y + m_pimpl->m_z * m_pimpl->m_z);
}

Vec3 GE::Quaternion::RotateVector(Vec3 A) const
{
  Quaternion q_a{ 0, A.x, A.y, A.z };
  const Quaternion& Q = *this;
  Quaternion result = Q * q_a * Q.Conjugate();
  return result.GetVec();
}

Vec3 GE::Quaternion::GetVec() const noexcept
{
  return Vec3(m_pimpl->m_x, m_pimpl->m_y, m_pimpl->m_z);
}

Quaternion& GE::Quaternion::operator=(const Quaternion& other)
{
  this->m_pimpl = MakeScope<Impl>(*other.m_pimpl.get());
  return *this;
}

GE::Quaternion::~Quaternion() = default;
