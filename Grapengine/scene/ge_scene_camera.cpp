#include "ge_scene_camera.hpp"

#include "core/ge_platform.hpp"
#include "math/ge_transformations.hpp"
#include "profiling/ge_profiler.hpp"

using namespace GE;

namespace
{
  constexpr auto DEFAULT_Z = 10;
  constexpr auto DEFAULT_FOV = 45.0f;
  constexpr auto DEFAULT_ORTHO_SIZE = 10.0f;
}

SceneCamera::SceneCamera() :
    m_position(Vec3{ 0, 0, DEFAULT_Z }),
    m_target(Vec3{ 0, 0, 0 }),
    m_viewport({ 1, 1 }),
    m_fov(DEFAULT_FOV),
    m_orthographic_size(DEFAULT_ORTHO_SIZE),
    m_projection_mode(ProjectionMode::PERSPECTIVE)
{
  GE_PROFILE;
  RecalculateProjection();
}

void SceneCamera::SetView(Vec3 position, Vec3 target)
{
  GE_PROFILE;
  m_position = position;
  m_target = target;
  RecalculateProjection();
}
void SceneCamera::SetViewport(Dimension vp)
{
  GE_PROFILE;
  m_viewport = vp;
  RecalculateProjection();
}

void SceneCamera::RecalculateProjection()
{
  GE_PROFILE;
  const f32 ar = f32(m_viewport.width) / f32(m_viewport.height);
  if (m_projection_mode == ProjectionMode::PERSPECTIVE)
  {
    m_projection = Transform::Perspective(m_fov, ar);
    return;
  }

  if (m_projection_mode == ProjectionMode::ORTHO)
  {
    const f32 ortho_left = -m_orthographic_size * ar * 0.5f;
    const f32 ortho_right = m_orthographic_size * ar * 0.5f;
    const f32 ortho_bot = -m_orthographic_size * 0.5f;
    const f32 ortho_top = m_orthographic_size * 0.5f;

    m_projection = Transform::Ortho(ortho_left, ortho_right, ortho_bot, ortho_top);
    return;
  }

  Platform::Unreachable();
}

Mat4 SceneCamera::GetViewProjection() const
{
  GE_PROFILE;
  return m_projection * Transform::LookAt(m_position, m_target);
}

void SceneCamera::SetProjectionMode(ProjectionMode mode)
{
  GE_PROFILE;
  m_projection_mode = mode;
  RecalculateProjection();
}

void SceneCamera::SetOrthographicSize(f32 size)
{
  GE_PROFILE;
  m_orthographic_size = size;
  RecalculateProjection();
}

void SceneCamera::SetFov(f32 fov)
{
  GE_PROFILE;
  m_fov = fov;
  RecalculateProjection();
}
