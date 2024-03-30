#include "renderer/ge_editor_camera.hpp"

#include "math/ge_geometry.hpp"
#include "math/ge_quaternions.hpp"

#include <core/ge_time_step.hpp>
#include <events/ge_event.hpp>
#include <input/ge_input.hpp>
#include <math/ge_transformations.hpp>
#include <math/ge_vector.hpp>

using namespace GE;

namespace
{
  constexpr f32 NEAR = 0.1f;
  constexpr f32 FAR = 1000.0f;
  constexpr Vec3 UP_DIR{ 0, 1, 0 };
}

struct EditorCamera::Impl
{
private:
  Mat4 projection_mat{};
  Mat4 view_mat{};
  Vec3 eye{ 2.5f, 2.5f, 12.0f };
  Vec3 focal_point{ 2.5f, 2.5f, 2.5f };
  Vec2 mouse_init_pos{};
  bool can_rotate = false;
  bool can_pan = false;

public:
  Impl(f32 fov, f32 aspectRatio)
  {
    projection_mat = Transform::Perspective(fov, aspectRatio, NEAR, FAR);
  }

  void ProcessMouseAction(f32 timestep)
  {
    const Vec2 mouse_pos = Input::Get().GetMouseXY();
    const Vec2 delta = (mouse_pos - mouse_init_pos);
    mouse_init_pos = mouse_pos;

    if (std::abs(delta.x) < std::numeric_limits<f32>::epsilon() &&
        std::abs(delta.y) < std::numeric_limits<f32>::epsilon())
      return;

    auto [x_eye, y_eye, z_eye] = Transform::LookAtVector(eye, focal_point, UP_DIR);

    if (can_rotate)
    {
      // Rotate a given point around plane contains x_eye
      const auto eye_origin_reference = (eye - focal_point).Normalize();
      const auto yaw_angle = -delta.x * timestep * 0.01f;
      const auto pitch_angle = -delta.y * timestep * 0.01f;
      const auto q =                               //
        Quaternion(yaw_angle, y_eye.Normalize()) * //
        Quaternion(pitch_angle, x_eye.Normalize());

      const auto new_eye_origin_reference = q.RotateVector(eye_origin_reference);

      const f32 eye_focal_pt_dist = focal_point.Distance(eye);
      const auto new_eye = focal_point + new_eye_origin_reference * eye_focal_pt_dist;

      auto new_view_direction = (focal_point - new_eye).Normalize();

      auto pos_angle = Geom::AngleBetween(new_view_direction, Vec3{ 0, 1, 0 });
      if (new_view_direction.y > 0 && pos_angle < 1)
        return;

      auto neg_angle = Geom::AngleBetween(new_view_direction, Vec3{ 0, -1, 0 });
      if (new_view_direction.y < 0 && neg_angle < 1)
        return;

      eye = new_eye;
    }

    if (can_pan)
    {
      const auto diff_x = x_eye * 0.01f * -delta.x;
      const auto diff_y = y_eye * 0.01f * delta.y;

      focal_point += diff_x + diff_y;
      eye += diff_x + diff_y;
    }
  }

  auto ViewProjection() { return projection_mat * view_mat; }

  void MouseZoom(const f32 delta)
  {
    const auto distance = focal_point.Distance(eye);
    const auto direction = (eye - focal_point).Normalize();
    eye = focal_point + direction * (distance + -delta * 15);
    UpdateView();
  }

  void UpdateView()
  {
    auto up = Vec3(0, 1, 0);
    view_mat = Transform::LookAt(eye, focal_point, up);
  }

  bool OnMouseScroll(MouseScrollData data)
  {
    const f32 delta = std::get<2>(data) * 0.01f;
    MouseZoom(delta);
    UpdateView();
    return true;
  }

  bool OnMousePressed(MouseButtonPressData data)
  {
    const auto& [_, bt] = data;
    if (bt == KeyCode::MOUSE_BT_LEFT)
    {
      mouse_init_pos = Input::Get().GetMouseXY();
      can_rotate = true;
      return true;
    }

    if (bt == KeyCode::MOUSE_BT_MIDDLE)
    {
      mouse_init_pos = Input::Get().GetMouseXY();
      can_pan = true;
      return true;
    }

    return false;
  }

  bool OnMouseReleased(MouseButtonPressData data)
  {
    const auto& [_, bt] = data;
    if (bt == KeyCode::MOUSE_BT_LEFT)
    {
      can_rotate = false;
      return true;
    }
    if (bt == KeyCode::MOUSE_BT_MIDDLE)
    {
      can_pan = false;
      return true;
    }
    return false;
  }
};

EditorCamera::EditorCamera() : m_pimpl(MakeScope<Impl>(0, 0)) {}

EditorCamera::EditorCamera(f32 fov, f32 aspectRatio) : m_pimpl(MakeScope<Impl>(fov, aspectRatio)) {}

EditorCamera::~EditorCamera() = default;

void EditorCamera::OnUpdate(TimeStep ts) const
{
  if (Input::Get().IsKeyPressed(KeyCode::K_LEFT_CONTROL))
    m_pimpl->ProcessMouseAction(ts.f());

  m_pimpl->UpdateView();
}

void EditorCamera::OnEvent(Event& event)
{
  Event::Dispatch(EvType::MOUSE_SCROLL,
                  event,
                  [this](const EvData& data)
                  { return m_pimpl->OnMouseScroll(*std::get_if<MouseScrollData>(&data)); });

  Event::Dispatch(EvType::MOUSE_BUTTON_PRESSED,
                  event,
                  [this](const EvData& data)
                  { return m_pimpl->OnMousePressed(*std::get_if<MouseButtonPressData>(&data)); });

  Event::Dispatch(EvType::MOUSE_BUTTON_RELEASE,
                  event,
                  [this](const EvData& data) {
                    return m_pimpl->OnMouseReleased(*std::get_if<MouseButtonReleaseData>(&data));
                  });
}

Mat4 EditorCamera::GetViewProjection() const
{
  return m_pimpl->ViewProjection();
}