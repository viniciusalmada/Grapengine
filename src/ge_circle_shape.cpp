#include "drawables/ge_circle_shape.hpp"

#include <drawables/ge_draw_primitive.hpp>
#include <renderer/ge_ishader_program.hpp>
#include <renderer/ge_renderer.hpp>
#include <renderer/ge_shaders_library.hpp>
#include <renderer/ge_vertices_data.hpp>

using namespace GE;

constexpr auto CIRCLE_POINTS = 30;

struct CircleShape::Impl
{
  f32 position_x = 0;
  f32 position_y = 0;
  f32 radius = 0;
  Color color{ Colors::WHITE };
  Ref<DrawPrimitive> draw_primitive;
  Shaders shader;
};

CircleShape::CircleShape(f32 x, f32 y, f32 radius, Color color, Shaders shader) :
    Drawable(shader), m_pimpl(MakeScope<Impl>())
{
  m_pimpl->position_x = x;
  m_pimpl->position_y = y;
  m_pimpl->radius = radius;
  m_pimpl->color = color;
  m_pimpl->shader = shader;

  auto layout = MakeRef<BufferLayout>(std::initializer_list<BufferElem>{
    BufferElem{ ShaderDataType::Float3, sizeof(f32) * 3, 0, false },
    BufferElem{ ShaderDataType::Float4, sizeof(f32) * 4, sizeof(f32) * 3, false } });

  auto positions = MakeRef<VerticesData>(layout);

  positions->PushData(Vec3{ x, y, -1000 }, color.ToVec4());

  auto indices = MakeRef<std::vector<u32>>();
  indices->reserve(CIRCLE_POINTS * 3);

  const f32 total = CIRCLE_POINTS;
  for (u32 i = 0; i < CIRCLE_POINTS; ++i)
  {
    const f32 angle = (f32)i / total * 2 * std::numbers::pi_v<f32>;
    const f32 circle_x = std::cos(angle) * radius + x;
    const f32 circle_y = std::sin(angle) * radius + y;
    auto pos = Vec3(circle_x, circle_y, 0.0f);
    positions->PushData(pos, color.ToVec4());

    indices->emplace_back(0);
    indices->emplace_back(i + 1);
    indices->emplace_back(i + 2);
  }
  indices->back() = 1;

  m_pimpl->draw_primitive = MakeRef<DrawPrimitive>(positions, indices);
}

CircleShape::~CircleShape() = default;

void CircleShape::Draw() const
{
  ShadersLibrary::Get().Activate(m_pimpl->shader);
  m_pimpl->draw_primitive->Draw();
}
