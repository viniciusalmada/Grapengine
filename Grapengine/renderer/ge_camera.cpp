// #include "renderer/ge_camera.hpp"
//
// #include "math/ge_transformations.hpp"
//
// #include <utils/ge_random.hpp>
//
// using namespace GE;
//
// namespace
//{
//   constexpr Vec3 UP_DIR = { 0.0f, 1.0f, 0.0f };
//   constexpr f32 FOV = 45;
//   constexpr f32 NEAR_FRUSTUM = 0.1f;
//   constexpr f32 FAR_FRUSTUM = 100;
//
//   f32 ClampPitch(const f32 pitch)
//   {
//     return std::clamp(pitch, 91.0f, 269.0f);
//   }
//
//   Vec3 CalculateDirection(f32 pitch, const f32 yaw)
//   {
//     // f32 yaw = 0;
//     const auto pitch_rad = Transform::Deg2Rad(pitch);
//     const auto yaw_rad = Transform::Deg2Rad(yaw);
//
//     // Pitch – plane YZ – 0 degree (camera back)
//     const f32 coord_z_pitch = std::cos(pitch_rad);
//     const f32 coord_y_dir = std::sin(pitch_rad);
//
//     const f32& hypotenuse = coord_z_pitch;
//
//     // cosine of yaw = Z / Hypotenuse
//     const f32 coord_z_dir = std::cos(yaw_rad) * hypotenuse;
//
//     // sine of yaw = X / Hypotenuse
//     const f32 coord_x_dir = std::sin(yaw_rad) * hypotenuse;
//
//     return Vec3{ coord_x_dir, coord_y_dir, coord_z_dir };
//   }
//
//   Vec3 CalculateLocation(const Vec3& center, const Vec3& target, f32 diffX, f32 diffY)
//   {
//     const auto& [x_eye, y_eye, z_eye] = Transform::LookAtVector(center, target, UP_DIR);
//
//     const Vec3 new_location = center + x_eye * diffX + y_eye * diffY;
//
//     return new_location;
//   }
// }
//
// struct Camera::Impl
//{
//   f32 aspect_ratio = 1;
//   f32 aim_sensibility = 0.05f;
//   f32 pan_sensibility = 0.05f;
//   Vec3 eye{};
//   Vec3 front{};
//   Vec3 temp_eye{};
//   Vec3 temp_front{};
//   f32 pitch_angle = 0;
//   f32 yaw_angle = 0;
//   bool in_aiming = false;
//   Vec2 aiming_reference_pt{};
//   bool in_movement = false;
//   Vec2 movement_reference_pt{};
//   bool in_rotating = false;
//   Vec2 rotating_reference_pt{};
//
//   void CalculateEyeFront()
//   {
//     const auto dir = CalculateDirection(pitch_angle, yaw_angle);
//     if (in_movement)
//       temp_front = temp_eye + dir;
//     else
//     {
//       front = eye + dir;
//       temp_front = front;
//       temp_eye = eye;
//     }
//   }
//
//   void UpdatePitchYaw(f32 diffPitch, f32 diffYaw)
//   {
//     if (in_aiming)
//     {
//       const auto pitch = pitch_angle + diffPitch * aim_sensibility;
//       const auto yaw = yaw_angle + diffYaw * aim_sensibility;
//       front = eye + CalculateDirection(ClampPitch(pitch), yaw);
//       return;
//     }
//     pitch_angle += diffPitch * aim_sensibility;
//     pitch_angle = ClampPitch(pitch_angle);
//     yaw_angle += diffYaw * aim_sensibility;
//     CalculateEyeFront();
//   }
//
//   void UpdateLocation(f32 diffX, f32 diffY)
//   {
//     if (in_movement)
//     {
//       temp_eye = CalculateLocation(eye, front, diffX * pan_sensibility, diffY * pan_sensibility);
//       CalculateEyeFront();
//       return;
//     }
//     eye = temp_eye;
//     front = temp_front;
//     CalculateEyeFront();
//   }
//
//   void UpdateZ(f32 diffY)
//   {
//     const auto& [x_eye, y_eye, z_eye] = Transform::LookAtVector(eye, front, UP_DIR);
//     eye = eye + z_eye * diffY;
//     CalculateEyeFront();
//   }
// };
//
// Camera::Camera(const f32 aspectRatio, const Vec3& eye, const Vec3& dir) :
//     m_pimpl(MakeScope<Impl>())
//{
//   m_pimpl->aspect_ratio = aspectRatio;
//   m_pimpl->eye = eye;
//   m_pimpl->front = dir;
// }
//
// Camera::Camera(const f32 aspectRatio, const Vec3& eye, const f32 pitch, const f32 yaw) :
//     m_pimpl(MakeScope<Impl>())
//{
//   m_pimpl->aspect_ratio = aspectRatio;
//   m_pimpl->eye = eye;
//   m_pimpl->temp_eye = eye;
//   m_pimpl->pitch_angle = pitch;
//   m_pimpl->yaw_angle = yaw;
//   m_pimpl->CalculateEyeFront();
// }
//
// Camera::~Camera() = default;
//
// Mat4 Camera::GetViewProjection() const
//{
//   auto& e = m_pimpl->in_movement ? m_pimpl->temp_eye : m_pimpl->eye;
//   auto& f = m_pimpl->in_movement ? m_pimpl->temp_front : m_pimpl->front;
//   const auto view = Transform::LookAt(e, f, UP_DIR);
//   const auto proj = Transform::Perspective(FOV, m_pimpl->aspect_ratio, NEAR_FRUSTUM,
//   FAR_FRUSTUM); return proj * view;
// }
//
// void Camera::SetAspectRatio(const f32 ratio) const
//{
//   m_pimpl->aspect_ratio = ratio;
// }
//
// void Camera::StartAiming(Vec2 referencePoint) const
//{
//   m_pimpl->in_aiming = true;
//   m_pimpl->aiming_reference_pt = referencePoint;
// }
//
// bool Camera::IsAiming() const
//{
//   return m_pimpl->in_aiming;
// }
//
// void Camera::StopAiming() const
//{
//   m_pimpl->in_aiming = false;
// }
//
// void Camera::ChangeAimPoint(Vec2 currentPoint) const
//{
//   const auto [x, y] = m_pimpl->aiming_reference_pt - currentPoint;
//   m_pimpl->UpdatePitchYaw(y, -x);
// }
//
// bool GE::Camera::IsMoving() const
//{
//   return m_pimpl->in_movement;
// }
//
// void GE::Camera::StartMoving(Vec2 referencePoint) const
//{
//   m_pimpl->in_movement = true;
//   m_pimpl->movement_reference_pt = referencePoint;
// }
//
// void GE::Camera::StopMoving() const
//{
//   m_pimpl->in_movement = false;
// }
//
// void GE::Camera::ChangeLocation(GE::Vec2 currentPoint) const
//{
//   const auto [diff_x, diff_y] = m_pimpl->movement_reference_pt - currentPoint;
//   m_pimpl->UpdateLocation(diff_x, -diff_y);
// }
//
// bool Camera::IsRotating() const
//{
//   return m_pimpl->in_rotating;
// }
//
// void Camera::StartRotating(Vec2 referencePoint) const
//{
//   m_pimpl->in_rotating = true;
//   m_pimpl->rotating_reference_pt = referencePoint;
// }
//
// void Camera::StopRotating() const
//{
//   m_pimpl->in_rotating = true;
// }
//
// void Camera::ChangeAngle(Vec2 currentPoint) const
//{
//   [[maybe_unused]] const auto [diff_x, diff_y] = m_pimpl->rotating_reference_pt - currentPoint;
// }
//
// void GE::Camera::SetZoom(f32 diffY) const
//{
//   m_pimpl->UpdateZ(diffY);
// }

#include "ge_camera.hpp"

using namespace GE;

Camera::Camera() = default;

void Camera::SetProjection(const Mat4& m)
{
  m_projection = m;
}
