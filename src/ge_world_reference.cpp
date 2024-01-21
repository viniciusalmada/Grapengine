#include "drawables/ge_world_reference.hpp"

#include <drawables/ge_cube.hpp>
#include <drawables/ge_cylinder.hpp>
#include <renderer/ge_shaders_library.hpp>
#include <renderer/ge_texture_2d.hpp>

using namespace GE;

namespace
{
  constexpr Vec3 ORIGIN{ 0, 0, 0 };
  constexpr float AXIS_RADIUS = 0.02f;
}

struct WorldReference::Impl
{
  Ref<Texture2D> blank_texture;
  Ref<Cube> platform;
  Ref<Cylinder> x_axis;
  Ref<Cylinder> y_axis;
  Ref<Cylinder> z_axis;
};

GE::WorldReference::WorldReference() : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->blank_texture = MakeRef<Texture2D>();
  m_pimpl->platform = MakeRef<Cube>(0,
                                    0,
                                    0,
                                    Color{ 0xAAAAAAFF },
                                    Shaders::POSITION_AND_TEXTURE2D,
                                    m_pimpl->blank_texture);
  m_pimpl->x_axis = MakeRef<Cylinder>(Shaders::POSITION_AND_TEXTURE2D,
                                      AXIS_RADIUS,
                                      ORIGIN,
                                      Vec3{ 1, 0, 0 },
                                      5.0f,
                                      Color{ 0xFF3333AA },
                                      m_pimpl->blank_texture);
  m_pimpl->y_axis = MakeRef<Cylinder>(Shaders::POSITION_AND_TEXTURE2D,
                                      AXIS_RADIUS,
                                      ORIGIN,
                                      Vec3{ 0, 1, 0 },
                                      5.0f,
                                      Color{ 0x33FF33AA },
                                      m_pimpl->blank_texture);
  m_pimpl->z_axis = MakeRef<Cylinder>(Shaders::POSITION_AND_TEXTURE2D,
                                      AXIS_RADIUS,
                                      ORIGIN,
                                      Vec3{ 0, 0, 1 },
                                      5.0f,
                                      Color{ 0x3333FFAA },
                                      m_pimpl->blank_texture);
  m_pimpl->platform->SetScale(5.f, AXIS_RADIUS, 5.f);
  m_pimpl->platform->SetTranslate(2.5f, 0, 2.5f);
}

void GE::WorldReference::DrawBatch()
{
  m_pimpl->platform->Draw();
  m_pimpl->x_axis->Draw();
  m_pimpl->y_axis->Draw();
  m_pimpl->z_axis->Draw();
}

GE::WorldReference::~WorldReference() = default;
