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
  float position_x = 0;
  float position_y = 0;
  float radius = 0;
  Color color{};
  Ref<DrawPrimitive> draw_primitive;
  Shaders shader;
};

CircleShape::CircleShape(float x, float y, float radius, Color color, Shaders shader) :
    Drawable(shader), m_pimpl(MakeScope<Impl>())
{
  m_pimpl->position_x = x;
  m_pimpl->position_y = y;
  m_pimpl->radius = radius;
  m_pimpl->color = color;
  m_pimpl->shader = shader;

  auto layout = MakeRef<BufferLayout>(std::initializer_list<BufferElem>{
    BufferElem{ "in_position", ShaderDataType::Float3, sizeof(float) * 3, 0, false },
    BufferElem{ "in_color",
                ShaderDataType::Float4,
                sizeof(float) * 4,
                sizeof(float) * 3,
                false } });

  auto positions = MakeRef<VerticesData>(layout);

  positions->PushData(Vec3{ x, y, -1000}, color.ToVec4());

  auto indices = MakeRef<std::vector<u32>>();
  indices->reserve(CIRCLE_POINTS * 3);

  const float total = CIRCLE_POINTS;
  for (u32 i = 0; i < CIRCLE_POINTS; ++i)
  {
    const float angle = (float)i / total * 2 * std::numbers::pi_v<float>;
    const float circle_x = cos(angle) * radius + x;
    const float circle_y = sin(angle) * radius + y;
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
