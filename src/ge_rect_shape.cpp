#include "drawables/ge_rect_shape.hpp"

#include <drawables/ge_draw_primitive.hpp>
#include <renderer/ge_ishader_program.hpp>
#include <renderer/ge_renderer.hpp>
#include <renderer/ge_shaders_library.hpp>
#include <renderer/ge_texture_2d.hpp>
#include <renderer/ge_vertices_data.hpp>
#include <renderer/shader_programs/ge_pos_tex_shader.hpp>

using namespace GE;

struct RectShape::Impl
{
  //  f32 position_x = 0;
  //  f32 position_y = 0;
  //  f32 width = 0;
  //  f32 height = 0;
  Color color{ 0 };
  Ref<DrawPrimitive> draw_primitive;
  Shaders shader;
  Ref<Texture2D> tex = nullptr;
};

RectShape::RectShape(Vec3 botLeft,
                     Vec3 botRight,
                     Vec3 topRight,
                     Vec3 topLeft,
                     Color color,
                     Shaders shader,
                     Ref<Texture2D> tex) :
    Drawable(shader), m_pimpl(MakeScope<Impl>())
{
  m_pimpl->color = color;
  m_pimpl->shader = shader;
  m_pimpl->tex = tex;

  const auto layout = ShadersLibrary::Get().GetLayout(Shaders::POSITION_AND_TEXTURE2D);

  auto positions = MakeRef<VerticesData>(layout);
  positions->PushData(botLeft, Vec2{ 0, 0 }, color.ToVec4());
  positions->PushData(botRight, Vec2{ 1, 0 }, color.ToVec4());
  positions->PushData(topRight, Vec2{ 1, 1 }, color.ToVec4());
  positions->PushData(topLeft, Vec2{ 0, 1 }, color.ToVec4());

  Ref<std::vector<u32>> indices =
    MakeRef<std::vector<u32>>(std::initializer_list<u32>{ 0, 1, 2, 2, 3, 0 });

  m_pimpl->draw_primitive = MakeRef<DrawPrimitive>(positions, indices);
}

void RectShape::Draw() const
{
  m_pimpl->tex->Bind(0);
  ShadersLibrary::Get().Activate(m_pimpl->shader);
  auto shader =
    std::static_pointer_cast<PosAndTex2DShader>(ShadersLibrary::Get().GetShader(m_pimpl->shader));
  shader->UpdateModelMatrix({});
  shader->UpdateTexture(0);

  m_pimpl->draw_primitive->Draw();
}

// Vec2 RectShape::GetPosition() const
//{
//   return Vec2{ m_pimpl->position_x, m_pimpl->position_y };
// }
//
// void RectShape::SetPosition(f32 x, f32 y) const
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
