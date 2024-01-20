#include "drawables/ge_rect_shape.hpp"

#include <drawables/ge_draw_primitive.hpp>
#include <renderer/ge_ishader_program.hpp>
#include <renderer/ge_renderer.hpp>
#include <renderer/ge_shaders_library.hpp>
#include <renderer/ge_texture_2d.hpp>
#include <renderer/ge_vertices_data.hpp>

struct RectShape::Impl
{
  //  float position_x = 0;
  //  float position_y = 0;
  //  float width = 0;
  //  float height = 0;
  Color color{};
  Ref<DrawPrimitive> draw_primitive;
  Shaders shader;
  Ref<Texture2D> tex = nullptr;
};

RectShape::RectShape(float x, float y, float width, float height, Color color, Shaders shader) :
    RectShape(Vec3{ x, y, 0.0f },
              Vec3{ x + width, y, 0.0f },
              Vec3{ x + width, y + height, 0.0f },
              Vec3{ x, y + height, 0.0f },
              color,
              shader)
{
}

RectShape::RectShape(Vec3 botLeft,
                     Vec3 botRight,
                     Vec3 topRight,
                     Vec3 topLeft,
                     Color color,
                     Shaders shader,
                     std::string path) :
    Drawable(shader), m_pimpl(MakeScope<Impl>())
{
  //  m_pimpl->position_x = (x);
  //  m_pimpl->position_y = (y);
  //  m_pimpl->width = (width);
  //  m_pimpl->height = (height);
  m_pimpl->color = color;
  m_pimpl->shader = shader;
  if (!path.empty())
  {
    m_pimpl->tex = MakeRef<Texture2D>(std::filesystem::path{ path });
    m_pimpl->tex->Bind(0);
  }

  const auto layout = MakeRef<BufferLayout>(std::initializer_list<BufferElem>{
    { "in_position", ShaderDataType::Float3, sizeof(float) * 3, 0, false },
    { "in_texture_coord", ShaderDataType::Float2, sizeof(float) * 2, sizeof(float) * 3, false },
    { "in_use_color", ShaderDataType::Float, sizeof(float), sizeof(float) * 5, false },
    { "in_color", ShaderDataType::Float4, sizeof(float) * 4, sizeof(float) * 6, false } });

  auto positions = MakeRef<VerticesData>(layout);
  positions->PushData(botLeft, Vec2{ 0, 0 }, m_pimpl->tex == nullptr ? 1.0f : 0, color.ToVec4());
  positions->PushData(botRight, Vec2{ 1, 0 }, m_pimpl->tex == nullptr ? 1.0f : 0, color.ToVec4());
  positions->PushData(topRight, Vec2{ 1, 1 }, m_pimpl->tex == nullptr ? 1.0f : 0, color.ToVec4());
  positions->PushData(topLeft, Vec2{ 0, 1 }, m_pimpl->tex == nullptr ? 1.0f : 0, color.ToVec4());

  Ref<std::vector<u32>> indices =
    MakeRef<std::vector<u32>>(std::initializer_list<u32>{ 0, 1, 2, 2, 3, 0 });

  m_pimpl->draw_primitive = MakeRef<DrawPrimitive>(positions, indices);
}

void RectShape::Draw() const
{
  ShadersLibrary::Get().Activate(m_pimpl->shader);
  m_pimpl->draw_primitive->Draw();
}

// Vec2 RectShape::GetPosition() const
//{
//   return Vec2{ m_pimpl->position_x, m_pimpl->position_y };
// }
//
// void RectShape::SetPosition(float x, float y) const
//{
//   m_pimpl->position_x = x;
//   m_pimpl->position_y = y;
//   //  Ref<std::vector<SimpleVertexData>> positions = MakeRef<std::vector<SimpleVertexData>>();
//   //  positions->reserve(4);
//   //  positions->emplace_back(Vec3{ x, y, 0.0f }, Vec4{ 0.f, 0.f, 1.0f, 1.0f });
//   //  positions->emplace_back(Vec3{ x + m_pimpl->width, y, 0.0f }, Vec4{ 0.f, 0.f, 1.0f, 1.0f });
//   //  positions->emplace_back(Vec3{ x + m_pimpl->width, y + m_pimpl->height, 0.0f },
//   //                          Vec4{ 0.f, 0.f, 1.0f, 1.0f });
//   //  positions->emplace_back(Vec3{ x, y + m_pimpl->height, 0.0f }, Vec4{ 0.f, 0.f, 1.0f, 1.0f
//   });
//   //  m_pimpl->draw_primitive->UpdateVerticesData(positions);
// }

RectShape::~RectShape() = default;
