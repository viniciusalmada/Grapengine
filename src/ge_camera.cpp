#include "renderer/ge_camera.hpp"

#include "math/ge_transformations.hpp"

using namespace GE;

namespace
{
  constexpr Vec3 UP_DIR = { 0.0f, 1.0f, 0.0f };
  constexpr float FOV = 45;
  constexpr float NEAR_FRUSTUM = 0.1;
  constexpr float FAR_FRUSTUM = 100;

  float ClampPitch(const float pitch)
  {
    return std::clamp(pitch, 91.0f, 269.0f);
  }

  Vec3 CalculateDirection(float pitch, const float yaw)
  {
    std::cout << std::format("{}", pitch) << std::endl;
    // float yaw = 0;
    const auto pitch_rad = Transform::Deg2Rad(pitch);
    const auto yaw_rad = Transform::Deg2Rad(yaw);

    // Pitch – plane YZ – 0 degree (camera back)
    const float coord_z_pitch = std::cosf(pitch_rad);
    const float coord_y_dir = std::sinf(pitch_rad);

    const float& hypotenuse = coord_z_pitch;

    // cosine of yaw = Z / Hypotenuse
    const float coord_z_dir = std::cosf(yaw_rad) * hypotenuse;

    // sine of yaw = X / Hypotenuse
    const float coord_x_dir = std::sinf(yaw_rad) * hypotenuse;

    return Vec3{ coord_x_dir, coord_y_dir, coord_z_dir };
  }
}

struct Camera::Impl
{
  float aspect_ratio = 1;
  float sensibility = 0.1f;
  Vec3 eye{};
  Vec3 front{};
  float pitch_angle = 0;
  float yaw_angle = 0;
  bool in_aiming = false;
  Vec2 aiming_reference_pt{};

  void CalculateEyeFront()
  {
    const auto dir = CalculateDirection(pitch_angle, yaw_angle);
    front = eye + dir;
  }

  void UpdatePitchYaw(float diffPitch, float diffYaw)
  {
    if (in_aiming)
    {
      const auto pitch = pitch_angle + diffPitch * sensibility;
      const auto yaw = yaw_angle + diffYaw * sensibility;
      front = eye + CalculateDirection(ClampPitch(pitch), yaw);
      return;
    }
    pitch_angle += diffPitch * sensibility;
    pitch_angle = ClampPitch(pitch_angle);
    yaw_angle += diffYaw * sensibility;
    CalculateEyeFront();
  }
};

Camera::Camera(const float aspectRatio, const Vec3& eye, const Vec3& dir) :
    m_pimpl(MakeScope<Impl>())
{
  m_pimpl->aspect_ratio = aspectRatio;
  m_pimpl->eye = eye;
  m_pimpl->front = dir;
}

Camera::Camera(const float aspectRatio, const Vec3& eye, const float pitch, const float yaw) :
    m_pimpl(MakeScope<Impl>())
{
  m_pimpl->aspect_ratio = aspectRatio;
  m_pimpl->eye = eye;
  m_pimpl->pitch_angle = pitch;
  m_pimpl->yaw_angle = yaw;
  m_pimpl->CalculateEyeFront();
}

Camera::~Camera() = default;

Mat4 Camera::GetViewProjection() const
{
  const auto view = Transform::LookAt(m_pimpl->eye, m_pimpl->front, UP_DIR);
  const auto proj = Transform::Perspective(FOV, m_pimpl->aspect_ratio, NEAR_FRUSTUM, FAR_FRUSTUM);
  return proj * view;
}

void Camera::SetAspectRatio(const float ratio) const
{
  m_pimpl->aspect_ratio = ratio;
}

Camera& Camera::operator=(const Camera& other)
{
  this->m_pimpl = MakeScope<Impl>();
  this->m_pimpl->front = other.m_pimpl->front;
  this->m_pimpl->eye = other.m_pimpl->eye;
  return *this;
}

void Camera::StartAiming(Vec2 referencePoint) const
{
  m_pimpl->in_aiming = true;
  m_pimpl->aiming_reference_pt = referencePoint;
}

bool Camera::IsAiming() const
{
  return m_pimpl->in_aiming;
}

void Camera::StopAiming() const
{
  m_pimpl->in_aiming = false;
}

void Camera::ChangeAimPoint(Vec2 currentPoint) const
{
  const auto [x, y] = m_pimpl->aiming_reference_pt - currentPoint;
  m_pimpl->UpdatePitchYaw(y, -x);
}