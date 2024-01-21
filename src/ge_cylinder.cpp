#include "drawables/ge_cylinder.hpp"

#include <drawables/ge_color.hpp>
#include <drawables/ge_draw_primitive.hpp>
#include <renderer/ge_buffer_layout.hpp>
#include <renderer/ge_shader_data_types.hpp>
#include <renderer/ge_shaders_library.hpp>
#include <renderer/ge_vertices_data.hpp>
#include <utils/ge_random.hpp>

using namespace GE;

struct Cylinder::Impl
{
  Color color{};
  Ref<DrawPrimitive> draw_primitive;
  Shaders shader;
};

constexpr auto SLICES = 20.0f;
// constexpr auto STACKS = 8;

Cylinder::Cylinder(const Shaders shader,
                   const float radius,
                   const Vec3& basePoint,
                   const Vec3& direction,
                   const float height,
                   Color color) :
    Drawable(shader), m_pimpl(MakeScope<Impl>())
{
  m_pimpl->shader = shader;
  m_pimpl->color = color;
  const auto layout = MakeRef<BufferLayout>(std::initializer_list<BufferElem>{
    { "in_position", ShaderDataType::Float3, sizeof(float) * 3, 0, false },
    { "in_texture_coord", ShaderDataType::Float2, sizeof(float) * 2, sizeof(float) * 3, false },
    { "in_use_color", ShaderDataType::Float, sizeof(float), sizeof(float) * 5, false },
    { "in_color", ShaderDataType::Float4, sizeof(float) * 4, sizeof(float) * 6, false } });

  const Vec3 normal = direction.Normalize();
  const Vec3 ref_random{ Random::GenFloat(0, 1), Random::GenFloat(0, 1), Random::GenFloat(0, 1) };
  const Vec3 reference = (ref_random - normal * normal.Dot(ref_random)).Normalize();
  std::vector<Vec3> base_pts;
  std::vector<Vec3> final_pts;
  for (u32 i = 0; i < SLICES; i++)
  {
    const float theta = 2.0f * std::numbers::pi_v<float> * i / SLICES;
    Vec3 pt = reference * std::cos(theta) + normal.Cross(reference) * std::sin(theta);
    Vec3 pt_base = basePoint + pt * radius;
    Vec3 pt_final = pt_base + normal * height;
    base_pts.push_back(pt_base);
    final_pts.push_back(pt_final);
  }

  const Ref<VerticesData> positions = MakeRef<VerticesData>(layout);
  for (u32 i = 0; i < base_pts.size(); ++i)
  {
    positions->PushData(base_pts[i], Vec2{}, 1.0f, color.ToVec4());
    positions->PushData(final_pts[i], Vec2{}, 1.0f, color.ToVec4());
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
  ShadersLibrary::Get().Activate(m_pimpl->shader);
  m_pimpl->draw_primitive->Draw();
}
