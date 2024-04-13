#include "drawables/ge_world_reference.hpp"

#include <drawables/ge_cube.hpp>
#include <drawables/ge_cylinder.hpp>
#include <renderer/ge_texture_2d.hpp>

using namespace GE;

namespace
{
  constexpr Vec3 ORIGIN{ 0, 0, 0 };
  constexpr f32 AXIS_RADIUS = 0.02f;
}

GE::WorldReference::WorldReference(const Ref<IShaderProgram>& shader, u64 platformSize)
{
  m_shader = shader;
  m_platform_side_size = platformSize;
  const f32 SIDE_SIZE = static_cast<f32>(m_platform_side_size);
  m_blank_texture = MakeRef<Texture2D>();
  m_platform = MakeRef<Cube>(Color{ 0xAAAAAAFF }, m_shader, m_blank_texture);
  m_platform->SetScale(SIDE_SIZE, AXIS_RADIUS, SIDE_SIZE);
  m_platform->SetTranslate(SIDE_SIZE / 2, 0, SIDE_SIZE / 2);

  m_x_axis = MakeRef<Cylinder>(m_shader,
                               AXIS_RADIUS,
                               ORIGIN,
                               Vec3{ 1, 0, 0 },
                               SIDE_SIZE * 10,
                               Colors::RED,
                               m_blank_texture);
  m_y_axis = MakeRef<Cylinder>(m_shader,
                               AXIS_RADIUS,
                               ORIGIN,
                               Vec3{ 0, 1, 0 },
                               SIDE_SIZE * 10,
                               Colors::GREEN,
                               m_blank_texture);
  m_z_axis = MakeRef<Cylinder>(m_shader,
                               AXIS_RADIUS,
                               ORIGIN,
                               Vec3{ 0, 0, 1 },
                               SIDE_SIZE * 10,
                               Colors::BLUE,
                               m_blank_texture);
}

void WorldReference::DrawBatch() const
{
  m_shader->Activate();

  if (m_show_platform)
    m_platform->Draw();
  m_x_axis->Draw();
  m_y_axis->Draw();
  m_z_axis->Draw();
}

void GE::WorldReference::ShowPlatform(bool show)
{
  m_show_platform = show;
}

Ref<DrawingObject> GE::WorldReference::GetVAO() const
{
  return m_platform->GetVAO();
}

Mat4 GE::WorldReference::GetModelMatrix() const
{
  return m_platform->GetModelMatrix();
}

WorldReference::~WorldReference() = default;
