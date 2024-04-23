#include "ge_scene_camera.hpp"

#include "math/ge_transformations.hpp"

using namespace GE;

SceneCamera::SceneCamera() :
    m_position(Vec3{ 0, 0, 10 }), m_target(Vec3{ 0, 0, 0 }), m_viewport(1, 1)
{
  RecalculateProjection();
}

SceneCamera::SceneCamera(const SceneCamera& other) :
    m_position(other.m_position), m_target(other.m_target), m_viewport(other.m_viewport)
{
}

void SceneCamera::SetView(Vec3 position, Vec3 target)
{
  m_position = position;
  m_target = target;
  RecalculateProjection();
}
void SceneCamera::SetViewport(Dimension vp)
{
  m_viewport = vp;
  RecalculateProjection();
}

void SceneCamera::RecalculateProjection()
{
  const f32 ar = f32(m_viewport.width) / f32(m_viewport.height);
  // TODO revise fovy
  m_projection = Transform::Perspective(45.0f, ar);
}
