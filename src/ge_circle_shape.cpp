#include "ge_circle_shape.hpp"

#include <ge_draw_primitive.hpp>
#include <ge_renderer.hpp>

constexpr auto CIRCLE_POINTS = 30;

struct CircleShape::Impl
{
  float position_x;
  float position_y;
  float radius;
  Ref<DrawPrimitive> draw_primitive;
};

CircleShape::CircleShape(float x, float y, float radius) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->position_x = x;
  m_pimpl->position_y = y;
  m_pimpl->radius = radius;

  auto positions = MakeRef<std::vector<SimpleVertexData>>();
  positions->reserve(CIRCLE_POINTS + 1);

  constexpr Vec4 color{ 0.f, 0.f, 1.0f, 1.0f };
  positions->emplace_back(Vec3{ x, y, 0 }, color);

  auto indices = MakeRef<std::vector<u32>>();
  indices->reserve(CIRCLE_POINTS * 3);

  for (u32 i = 0, first_id = 1, sec_id = 2; i < CIRCLE_POINTS; ++i, ++first_id, ++sec_id)
  {
    const float angle =
      static_cast<float>(i) / static_cast<float>(CIRCLE_POINTS) * 2 * std::numbers::pi_v<float>;
    const float circle_x = cos(angle) * radius + x;
    const float circle_y = sin(angle) * radius + y;
    auto pos = Vec3(circle_x, circle_y, 0.0f);
    positions->emplace_back(pos, color);

    indices->emplace_back(0);
    indices->emplace_back(first_id);
    indices->emplace_back(sec_id);
  }
  indices->back() = 1;

  m_pimpl->draw_primitive = MakeRef<DrawPrimitive>(positions, indices);
}

CircleShape::~CircleShape() = default;

void CircleShape::Draw() const
{
  m_pimpl->draw_primitive->Draw();
}
