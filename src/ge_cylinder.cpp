#include "drawables/ge_cylinder.hpp"

#include <drawables/ge_color.hpp>
#include <drawables/ge_draw_primitive.hpp>
#include <renderer/ge_buffer_layout.hpp>
#include <renderer/ge_shader_data_types.hpp>
#include <renderer/ge_shaders_library.hpp>
#include <renderer/ge_texture_2d.hpp>
#include <renderer/ge_vertices_data.hpp>
#include <renderer/shader_programs/ge_pos_tex_shader.hpp>
#include <utility>
#include <utils/ge_random.hpp>

using namespace GE;

struct Cylinder::Impl
{
  Color color{ 0 };
  Ref<DrawPrimitive> draw_primitive;
  Shaders shader;
  Ref<Texture2D> texture;
};

constexpr auto SLICES = 20ul;
// constexpr auto STACKS = 8;

Cylinder::Cylinder(const Shaders shader,
                   const float radius,
                   const Vec3& basePoint,
                   const Vec3& direction,
                   const float height,
                   Color color,
                   Ref<Texture2D> texture2D) :
    Drawable(shader), m_pimpl(MakeScope<Impl>())
{
  m_pimpl->shader = shader;
  m_pimpl->color = color;
  m_pimpl->texture = std::move(texture2D);
  auto layout = ShadersLibrary::Get().GetLayout(shader);

  const Vec3 normal = direction.Normalize();
  const Vec3 ref_random{ Random::GenFloat(0, 1), Random::GenFloat(0, 1), Random::GenFloat(0, 1) };
  const Vec3 reference = (ref_random - normal * normal.Dot(ref_random)).Normalize();
  std::vector<Vec3> base_pts;
  std::vector<Vec3> final_pts;
  for (u32 i = 0; i < SLICES; i++)
  {
    const float slice_percent = static_cast<float>(i) / static_cast<float>(SLICES);
    const float theta = 2.0f * std::numbers::pi_v<float> * slice_percent;
    Vec3 pt = reference * std::cos(theta) + normal.Cross(reference) * std::sin(theta);
    Vec3 pt_base = basePoint + pt * radius;
    Vec3 pt_final = pt_base + normal * height;
    base_pts.push_back(pt_base);
    final_pts.push_back(pt_final);
  }

  const Ref<VerticesData> positions = MakeRef<VerticesData>(layout);
  for (u32 i = 0; i < base_pts.size(); ++i)
  {
    positions->PushData(base_pts[i], Vec2{ 1, 1 }, color.ToVec4());
    positions->PushData(final_pts[i], Vec2{ 1, 1 }, color.ToVec4());
  }

  const auto indices = MakeRef<std::vector<u32>>();
  for (int i = 0; i < static_cast<int>(SLICES * 2); i += 2)
  {
    indices->emplace_back(0 + i);
    indices->emplace_back(1 + i);
    indices->emplace_back(2 + i);

    indices->emplace_back(2 + i);
    indices->emplace_back(1 + i);
    indices->emplace_back(3 + i);
  }
  (*indices)[indices->size() - 6] = static_cast<u32>(SLICES * 2 - 2);
  (*indices)[indices->size() - 5] = 3;
  (*indices)[indices->size() - 4] = 0;
  (*indices)[indices->size() - 3] = 0;
  (*indices)[indices->size() - 2] = static_cast<u32>(SLICES * 2 - 1);
  (*indices)[indices->size() - 1] = 1;

  m_pimpl->draw_primitive = MakeRef<DrawPrimitive>(positions, indices);
}

Cylinder::~Cylinder() = default;

void Cylinder::Draw() const
{
  m_pimpl->texture->Bind(0);
  ShadersLibrary::Get().Activate(m_pimpl->shader);
  auto shader =
    std::static_pointer_cast<PosAndTex2DShader>(ShadersLibrary::Get().GetShader(m_pimpl->shader));
  shader->UpdateModelMatrix(Mat4{});
  shader->UpdateTexture(0);
  m_pimpl->draw_primitive->Draw();
}
