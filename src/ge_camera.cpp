#include "renderer/ge_camera.hpp"

#include "math/ge_transformations.hpp"

namespace
{
  constexpr Vec3 UP_DIR = { 0.0f, 1.0f, 0.0f };
}

struct Camera::Impl
{
  Vec3 eye;
  Vec3 dir;
};

Camera::Camera(const Vec3& eye, const Vec3& dir) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->eye = eye;
  m_pimpl->dir = dir;
}

Camera::Camera(const Vec3& eye, float pitch, float /*yaw*/, float /*roll*/) :
    m_pimpl(MakeScope<Impl>())
{
  // Pitch – plane YZ
  float hor = std::cosf(Transform::Deg2Rad(pitch));
  float ver = std::sinf(Transform::Deg2Rad(pitch));
  this->m_pimpl->eye = eye;
  auto dir = eye + Vec3{0, hor, ver};
  this->m_pimpl->dir = dir;
}

Camera::~Camera() = default;

Mat4 Camera::GetViewProjection() const
{
  std::cout << m_pimpl->dir.x << ',' << m_pimpl->dir.y << ',' << m_pimpl->dir.z << std::endl;
  const auto view = Transform::LookAt(m_pimpl->eye, m_pimpl->dir, UP_DIR);
  const auto projection = Transform::Perspective(80, 1.0f, 0.1f, 100.0f);
  return projection * view;
}

Camera& Camera::operator=(const Camera& other)
{
  this->m_pimpl = MakeScope<Impl>();
  this->m_pimpl->dir = other.m_pimpl->dir;
  this->m_pimpl->eye = other.m_pimpl->eye;
  return *this;
}
