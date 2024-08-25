#include "drawables/ge_cylinder.hpp"

#include "drawables/ge_color.hpp"
#include "drawables/ge_drawing_object.hpp"
#include "profiling/ge_profiler.hpp"
#include "renderer/ge_texture_2d.hpp"
#include "utils/ge_random.hpp"

using namespace GE;

namespace
{
  constexpr auto SLICES = 20ul;
  // constexpr auto STACKS = 8;

  VerticesData BuildVerticesData(const GE::Vec3& basePoint,
                                 const f32 radius,
                                 const GE::Vec3& direction,
                                 const f32 height)
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

    VerticesData vertices_data;
    auto color = Colors::WHITE.ToVec4();
    for (u32 i = 0; i < base_pts.size(); ++i)
    {
      vertices_data.PushVerticesData(
        { base_pts[i], Vec2{ 1, 1 }, color, Vec3{ 0, 0, 0 }, Texture2D::EMPTY_TEX_SLOT });
      vertices_data.PushVerticesData(
        { final_pts[i], Vec2{ 1, 1 }, color, Vec3{ 0, 0, 0 }, Texture2D::EMPTY_TEX_SLOT });
    }

    return vertices_data;
  }

  auto BuildIndicesData()
  {
    std::vector<u32> indices;
    // NOLINTBEGIN(*-magic-numbers)
    for (int i = 0; i < static_cast<int>(SLICES * 2); i += 2)
    {
      indices.emplace_back(0 + i);
      indices.emplace_back(1 + i);
      indices.emplace_back(2 + i);

      indices.emplace_back(2 + i);
      indices.emplace_back(1 + i);
      indices.emplace_back(3 + i);
    }
    indices[indices.size() - 6] = static_cast<u32>(SLICES * 2 - 2);
    indices[indices.size() - 5] = 3;
    indices[indices.size() - 4] = 0;
    indices[indices.size() - 3] = 0;
    indices[indices.size() - 2] = static_cast<u32>(SLICES * 2 - 1);
    indices[indices.size() - 1] = 1;
    // NOLINTEND(*-magic-numbers)

    return indices;
  }

}

Cylinder::Cylinder(const GE::Vec3& basePoint,
                   const f32 radius,
                   const GE::Vec3& direction,
                   const f32 height) :
    m_drawable(BuildVerticesData(basePoint, radius, direction, height), BuildIndicesData())
{
}

const Drawable& Cylinder::GetDrawable() const
{
  return m_drawable;
}
