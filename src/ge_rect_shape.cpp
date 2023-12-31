#include "ge_rect_shape.hpp"

#include <ge_draw_primitive.hpp>
#include <ge_renderer.hpp>
#include <ge_vertices_data.hpp>

struct RectShape::Impl
{
  float position_x;
  float position_y;
  float width;
  float height;
  Ref<DrawPrimitive> draw_primitive;
};

RectShape::RectShape(float x, float y, float width, float height) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->position_x = (x);
  m_pimpl->position_y = (y);
  m_pimpl->width = (width);
  m_pimpl->height = (height);

  auto layout = MakeRef<BufferLayout>(std::initializer_list<BufferElem>{
    BufferElem{ "in_position", ShaderDataType::Float3, sizeof(float) * 3, 0, false },
    BufferElem{ "in_color",
                ShaderDataType::Float4,
                sizeof(float) * 4,
                sizeof(float) * 3,
                false } });

  auto positions = MakeRef<VerticesData>(layout);
  //  positions->reserve(4);
  positions->PushData(Vec3{ x, y, 0.0f }, Vec4{ 0.f, 0.f, 1.0f, 1.0f });
  positions->PushData(Vec3{ x + m_pimpl->width, y, 0.0f }, Vec4{ 0.f, 0.f, 1.0f, 1.0f });
  positions->PushData(Vec3{ x + m_pimpl->width, y + m_pimpl->height, 0.0f },
                      Vec4{ 0.f, 0.f, 1.0f, 1.0f });
  positions->PushData(Vec3{ x, y + m_pimpl->height, 0.0f }, Vec4{ 0.f, 0.f, 1.0f, 1.0f });

  Ref<std::vector<u32>> indices =
    MakeRef<std::vector<u32>>(std::initializer_list<u32>{ 0, 1, 2, 2, 3, 0 });

  m_pimpl->draw_primitive = MakeRef<DrawPrimitive>(positions, indices);
}

void RectShape::Draw() const
{
  m_pimpl->draw_primitive->Draw();
}

Vec2 RectShape::GetPosition() const
{
  return Vec2{ m_pimpl->position_x, m_pimpl->position_y };
}

void RectShape::SetPosition(float x, float y) const
{
  m_pimpl->position_x = x;
  m_pimpl->position_y = y;
  //  Ref<std::vector<SimpleVertexData>> positions = MakeRef<std::vector<SimpleVertexData>>();
  //  positions->reserve(4);
  //  positions->emplace_back(Vec3{ x, y, 0.0f }, Vec4{ 0.f, 0.f, 1.0f, 1.0f });
  //  positions->emplace_back(Vec3{ x + m_pimpl->width, y, 0.0f }, Vec4{ 0.f, 0.f, 1.0f, 1.0f });
  //  positions->emplace_back(Vec3{ x + m_pimpl->width, y + m_pimpl->height, 0.0f },
  //                          Vec4{ 0.f, 0.f, 1.0f, 1.0f });
  //  positions->emplace_back(Vec3{ x, y + m_pimpl->height, 0.0f }, Vec4{ 0.f, 0.f, 1.0f, 1.0f });
  //  m_pimpl->draw_primitive->UpdateVerticesData(positions);
}

RectShape::~RectShape() = default;
