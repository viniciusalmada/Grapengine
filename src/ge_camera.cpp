#include "renderer/ge_camera.hpp"

#include "math/ge_transformations.hpp"

namespace
{
  constexpr Vec3 UP_DIR = { 0.0f, 1.0f, 0.0f };
}

struct Camera::Impl
{
  Vec3 eye;
  Vec3 front;
};

Camera::Camera(const Vec3& eye, const Vec3& dir) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->eye = eye;
  m_pimpl->front = dir;
}

Camera::Camera(const Vec3& eye, float pitch, float yaw, float /*roll*/) : m_pimpl(MakeScope<Impl>())
{
  // Pitch – plane YZ – 0 degree (camera back)
  const float coord_z_pitch = std::cosf(Transform::Deg2Rad(pitch));
  const float coord_y_dir = std::sinf(Transform::Deg2Rad(pitch));

  const float hypotenuse = coord_z_pitch;

  // cosine of yaw = Z / Hypotenuse
  const float coord_z_dir = std::cosf(Transform::Deg2Rad(yaw)) * hypotenuse;

  // sine of yaw = X / Hypotenuse
  const float coord_x_dir = std::sinf(Transform::Deg2Rad(yaw)) * hypotenuse;

  auto dir = Vec3{ coord_x_dir, coord_y_dir, coord_z_dir };
  this->m_pimpl->eye = eye;
  this->m_pimpl->front = eye + dir;
}

Camera::~Camera() = default;

Mat4 Camera::GetViewProjection() const
{
  const auto view = Transform::LookAt(m_pimpl->eye, m_pimpl->front, UP_DIR);
  const auto projection = Transform::Perspective(80, 1.0f, 0.1f, 100.0f);
  return projection * view;
}

Camera& Camera::operator=(const Camera& other)
{
  this->m_pimpl = MakeScope<Impl>();
  this->m_pimpl->front = other.m_pimpl->front;
  this->m_pimpl->eye = other.m_pimpl->eye;
  return *this;
}
