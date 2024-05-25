#include "drawables/ge_cylinder.hpp"

#include "drawables/ge_color.hpp"
#include "drawables/ge_drawing_object.hpp"
#include "profiling/ge_profiler.hpp"
#include "renderer/ge_buffer_layout.hpp"
#include "renderer/ge_texture_2d.hpp"
#include "renderer/ge_vertices_data.hpp"
#include "renderer/shader_programs/ge_pos_tex_shader.hpp"
#include "utils/ge_random.hpp"

using namespace GE;

constexpr auto SLICES = 20ul;
// constexpr auto STACKS = 8;

Cylinder::Cylinder(const Ref<IShaderProgram>& shader,
                   const Vec3& basePoint,
                   const f32 radius,
                   const Vec3& direction,
                   const f32 height,
                   Color color,
                   Ref<Texture2D> texture2D) :
    Drawable(shader), m_color(color), m_shader(shader), m_texture(std::move(texture2D))
{
  GE_PROFILE;
  const Ref<const BufferLayout> layout = shader->GetLayout();

  const Vec3 normal = direction.Normalize();
  const Vec3 ref_random{ Random::GenFloat(0, 1), Random::GenFloat(0, 1), Random::GenFloat(0, 1) };
  const Vec3 reference = (ref_random - normal * normal.Dot(ref_random)).Normalize();
  std::vector<Vec3> base_pts;
  std::vector<Vec3> final_pts;
  for (u32 i = 0; i < SLICES; i++)
  {
    const f32 slice_percent = static_cast<f32>(i) / static_cast<f32>(SLICES);
    const f32 theta = 2.0f * std::numbers::pi_v<f32> * slice_percent;
    const Vec3 pt = reference * std::cos(theta) + normal.Cross(reference) * std::sin(theta);
    const Vec3 pt_base = basePoint + pt * radius;
    const Vec3 pt_final = pt_base + normal * height;
    base_pts.push_back(pt_base);
    final_pts.push_back(pt_final);
  }

  const Ref<VerticesData> positions = MakeRef<VerticesData>(layout);
  for (u32 i = 0; i < base_pts.size(); ++i)
  {
    if (layout->HasNormal())
    {
      positions->PushData(base_pts[i], Vec2{ 1, 1 }, color.ToVec4(), -direction.Normalize());
      positions->PushData(final_pts[i], Vec2{ 1, 1 }, color.ToVec4(), direction.Normalize());
    }
    else
    {
      positions->PushData(base_pts[i], Vec2{ 1, 1 }, color.ToVec4());
      positions->PushData(final_pts[i], Vec2{ 1, 1 }, color.ToVec4());
    }
  }

  // NOLINTBEGIN(*-magic-numbers)
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
  // NOLINTEND(*-magic-numbers)

  m_draw_primitive = MakeRef<DrawingObject>(positions, indices);
}

Cylinder::~Cylinder() = default;

void Cylinder::Draw() const
{
  GE_PROFILE;
  m_texture->Bind(0);
  m_shader->UpdateModelMatrix(Mat4{});
  m_shader->UpdateTexture(0);
  //  m_draw_primitive->Draw();
}
Ref<Cylinder> GE::Cylinder::Make(const Ref<IShaderProgram>& shader,
                                 const Vec3& basePoint,
                                 f32 radius,
                                 const Vec3& direction,
                                 f32 height,
                                 Color color,
                                 const Ref<Texture2D>& texture2D)
{
  return MakeRef<Cylinder>(shader, basePoint, radius, direction, height, color, texture2D);
}
