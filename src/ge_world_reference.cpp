#include "drawables/ge_world_reference.hpp"

#include <drawables/ge_cube.hpp>
#include <drawables/ge_cylinder.hpp>
#include <renderer/ge_texture_2d.hpp>
#include <renderer/shader_programs/ge_pos_tex_shader.hpp>

using namespace GE;

namespace
{
  constexpr Vec3 ORIGIN{ 0, 0, 0 };
  constexpr f32 AXIS_RADIUS = 0.02f;
  constexpr f32 SIDE_SIZE = 5.0f;
}

struct WorldReference::Impl
{
  Ref<IShaderProgram> shader;
  Ref<Texture2D> blank_texture;
  Ref<Cube> platform;
  Ref<Cylinder> x_axis;
  Ref<Cylinder> y_axis;
  Ref<Cylinder> z_axis;
};

GE::WorldReference::WorldReference() : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->shader = MakeRef<PosAndTex2DShader>();
  m_pimpl->blank_texture = MakeRef<Texture2D>();
  m_pimpl->platform = MakeRef<Cube>(Color{ 0xAAAAAAFF }, m_pimpl->shader, m_pimpl->blank_texture);
  m_pimpl->platform->SetScale(SIDE_SIZE, AXIS_RADIUS, SIDE_SIZE);
  m_pimpl->platform->SetTranslate(SIDE_SIZE / 2, 0, SIDE_SIZE / 2);

  m_pimpl->x_axis = MakeRef<Cylinder>(m_pimpl->shader,
                                      AXIS_RADIUS,
                                      ORIGIN,
                                      Vec3{ 1, 0, 0 },
                                      SIDE_SIZE * 10,
                                      Colors::RED,
                                      m_pimpl->blank_texture);
  m_pimpl->y_axis = MakeRef<Cylinder>(m_pimpl->shader,
                                      AXIS_RADIUS,
                                      ORIGIN,
                                      Vec3{ 0, 1, 0 },
                                      SIDE_SIZE * 10,
                                      Colors::GREEN,
                                      m_pimpl->blank_texture);
  m_pimpl->z_axis = MakeRef<Cylinder>(m_pimpl->shader,
                                      AXIS_RADIUS,
                                      ORIGIN,
                                      Vec3{ 0, 0, 1 },
                                      SIDE_SIZE * 10,
                                      Colors::BLUE,
                                      m_pimpl->blank_texture);
}

void WorldReference::DrawBatch() const
{
  m_pimpl->platform->Draw();
  m_pimpl->x_axis->Draw();
  m_pimpl->y_axis->Draw();
  m_pimpl->z_axis->Draw();
}

Ref<IShaderProgram> GE::WorldReference::GetShader() const
{
  return m_pimpl->shader;
}

WorldReference::~WorldReference() = default;
