#include "renderer/ge_editor_camera.hpp"

#include <core/ge_time_step.hpp>
#include <events/ge_event.hpp>
#include <input/ge_input.hpp>
#include <math/ge_transformations.hpp>
#include <math/ge_vector.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <drawables/ge_cube.hpp>
#include <drawables/ge_rect_shape.hpp>
#include <glm/gtx/quaternion.hpp>
#include <renderer/ge_shaders_library.hpp>
#include <renderer/ge_texture_2d.hpp>

using namespace GE;

namespace
{
  constexpr auto NEAR = 0.1f;
  constexpr auto FAR = 1000;

  Mat4 fromGLMMat4(glm::mat4 mat4)
  {
    Mat4 my_mat4{};
    for (u32 i = 0; i < 4; ++i)
    {
      for (u32 j = 0; j < 4; ++j)
      {
        my_mat4(i, j) = mat4[(i32)i][(i32)j];
      }
    }
    return my_mat4;
  }
  glm::mat4 fromMat4(Mat4 mat4)
  {
    glm::mat4 my_mat4{};
    for (u32 i = 0; i < 4; ++i)
    {
      for (u32 j = 0; j < 4; ++j)
      {
        my_mat4[(i32)i][(i32)j] = mat4(i, j);
      }
    }
    return my_mat4;
  }
}

struct EditorCamera::Impl
{
  f32 fov = 45;
  f32 aspect_ratio{ 0 };
  Mat4 projection_mat{};
  Mat4 view_mat{};
  Vec3 eye{};
  Vec3 focal_point{};
  Vec2 mouse_init_pos{};
  f32 distance = 10.0f;
  f32 pitch_angle = 0;
  f32 yaw_angle = 0;
  f32 viewport_width = 0;
  f32 viewport_height = 0;

  [[nodiscard]] Vec2 PanSpeed() const
  {
    f32 x = std::ranges::min(viewport_width / 1000.0f, 2.4f);
    f32 x_factor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

    f32 y = std::ranges::min(viewport_height / 1000.0f, 2.4f);
    f32 y_factor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

    return { x_factor, y_factor };
  }

  static constexpr f32 RotationSpeed() { return 1.8f; }

  [[nodiscard]] f32 ZoomSpeed() const
  {
    f32 dist = distance * 0.2f;
    dist = std::ranges::max(distance, 0.0f);
    f32 speed = dist * dist;
    speed = std::ranges::min(speed, 100.0f);
    return speed;
  }

  [[nodiscard]] glm::quat GetOrientation() const
  {
    return { glm::vec3(-pitch_angle, -yaw_angle, 0.0f) };
  }

  [[nodiscard]] Vec3 GetRightDirection() const
  {
    auto r = glm::rotate(GetOrientation(), glm::vec3{ 1.0f, 0.0f, 0.0f });
    return { r.x, r.y, r.z };
  }

  [[nodiscard]] Vec3 GetUpDirection() const
  {
    auto r = glm::rotate(GetOrientation(), glm::vec3{ 0.0f, 1.0f, 0.0f });
    return { r.x, r.y, r.z };
  }

  [[nodiscard]] Vec3 GetForwardDirection() const
  {
    auto r = glm::rotate(GetOrientation(), glm::vec3{ 0.0f, 0.0f, -1.0f });
    return { r.x, r.y, r.z };
  }

  void MousePan(const Vec2& delta)
  {
    const auto [x_speed, y_speed] = PanSpeed();
    focal_point += -GetRightDirection() * delta.x * x_speed * distance;
    focal_point += GetUpDirection() * delta.y * y_speed * distance;
    std::clog << focal_point.x << "," << focal_point.y << "," << focal_point.z << std::endl;
  }

  void MouseRotate(const Vec2& delta)
  {
    float yaw_sign = GetUpDirection().y < 0 ? -1 : +1;
    yaw_angle += yaw_sign * delta.x * RotationSpeed();
    pitch_angle += delta.y * RotationSpeed();
  }

  void MouseZoom(const f32 delta)
  {
    distance -= delta * ZoomSpeed();
    if (distance < 1.0f)
    {
      focal_point += GetForwardDirection();
      std::clog << focal_point.x << "," << focal_point.y << "," << focal_point.z << std::endl;
      distance = 1.0f;
    }
  }

  [[nodiscard]] Vec3 CalculatePosition() const
  {
    return focal_point - GetForwardDirection() * distance;
  }

  void UpdateView()
  {
    eye = CalculatePosition();

    auto orientation = GetOrientation();
    view_mat = Transform::Translate(eye.x, eye.y, eye.z) * fromGLMMat4(glm::toMat4(orientation));
    view_mat = fromGLMMat4(glm::inverse(fromMat4(view_mat)));
  }

  bool OnMouseScroll(MouseScrollData data)
  {
    const f32 delta = std::get<2>(data) * 0.01f;
    MouseZoom(delta);
    UpdateView();
    return true;
  }
};

EditorCamera& EditorCamera::operator=(const GE::EditorCamera& other)
{
  this->m_pimpl = MakeScope<Impl>();
  this->m_pimpl->fov = other.m_pimpl->fov;
  this->m_pimpl->aspect_ratio = other.m_pimpl->aspect_ratio;
  this->m_pimpl->projection_mat = other.m_pimpl->projection_mat;
  this->m_pimpl->view_mat = other.m_pimpl->view_mat;
  this->m_pimpl->eye = other.m_pimpl->eye;
  this->m_pimpl->focal_point = other.m_pimpl->focal_point;
  this->m_pimpl->mouse_init_pos = other.m_pimpl->mouse_init_pos;
  this->m_pimpl->distance = other.m_pimpl->distance;
  this->m_pimpl->pitch_angle = other.m_pimpl->pitch_angle;
  this->m_pimpl->yaw_angle = other.m_pimpl->yaw_angle;
  this->m_pimpl->viewport_width = other.m_pimpl->viewport_width;
  this->m_pimpl->viewport_height = other.m_pimpl->viewport_height;
  return *this;
}

EditorCamera::EditorCamera() : m_pimpl(MakeScope<Impl>()) {}

EditorCamera::EditorCamera(f32 fov, f32 aspectRatio) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->fov = fov;
  m_pimpl->aspect_ratio = aspectRatio;
  m_pimpl->projection_mat = Transform::Perspective(fov, aspectRatio, NEAR, FAR);
}

EditorCamera::~EditorCamera() = default;

void EditorCamera::OnUpdate(TimeStep) const
{
  if (Input::IsKeyPressed(KeyCode::K_LEFT_ALT))
  {
    const Vec2 mouse_pos = Input::GetMouseXY();
    const Vec2 delta = (mouse_pos - m_pimpl->mouse_init_pos) * 0.003f;
    m_pimpl->mouse_init_pos = mouse_pos;

    if (Input::IsMouseButtonPressed(KeyCode::MOUSE_BT_MIDDLE))
      m_pimpl->MousePan(delta);
    else if (Input::IsMouseButtonPressed(KeyCode::MOUSE_BT_LEFT))
      m_pimpl->MouseRotate(delta);
    else if (Input::IsMouseButtonPressed(KeyCode::MOUSE_BT_RIGHT))
      m_pimpl->MouseZoom(delta.y);
  }

  m_pimpl->UpdateView();
}

void EditorCamera::OnEvent(Event& event)
{
  Event::Dispatch(EvType::MOUSE_SCROLL,
                  event,
                  [this](const EvData& data)
                  { return m_pimpl->OnMouseScroll(*std::get_if<MouseScrollData>(&data)); });
}

Mat4 EditorCamera::GetViewProjection() const
{
  return m_pimpl->projection_mat * m_pimpl->view_mat;
}