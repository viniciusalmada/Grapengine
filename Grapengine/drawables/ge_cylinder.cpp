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

Cylinder::Cylinder(const GE::Vec3& basePoint,
                   const f32 radius,
                   const GE::Vec3& direction,
                   const f32 height,
                   GE::Color color) :
    m_color(color)
{
  GE_PROFILE;

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

  const Ptr<VerticesData> positions = MakeRef<VerticesData>();
  for (u32 i = 0; i < base_pts.size(); ++i)
  {
    positions->PushVerticesData(
      { base_pts[i], Vec2{ 1, 1 }, color.ToVec4(), -direction.Normalize() });
    positions->PushVerticesData(
      { final_pts[i], Vec2{ 1, 1 }, color.ToVec4(), direction.Normalize() });
  }

  // NOLINTBEGIN(*-magic-numbers)
  for (int i = 0; i < static_cast<int>(SLICES * 2); i += 2)
  {
    m_indices.emplace_back(0 + i);
    m_indices.emplace_back(1 + i);
    m_indices.emplace_back(2 + i);

    m_indices.emplace_back(2 + i);
    m_indices.emplace_back(1 + i);
    m_indices.emplace_back(3 + i);
  }
  m_indices[m_indices.size() - 6] = static_cast<u32>(SLICES * 2 - 2);
  m_indices[m_indices.size() - 5] = 3;
  m_indices[m_indices.size() - 4] = 0;
  m_indices[m_indices.size() - 3] = 0;
  m_indices[m_indices.size() - 2] = static_cast<u32>(SLICES * 2 - 1);
  m_indices[m_indices.size() - 1] = 1;
  // NOLINTEND(*-magic-numbers)
}

Cylinder::~Cylinder() = default;

VerticesData Cylinder::GetVerticesData(Color /*color*/) const
{
  return m_vertices;
}
const std::vector<u32>& Cylinder::GetIndicesData() const
{
  return m_indices;
}
