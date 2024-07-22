#include "drawables/ge_mesh.hpp"

#include "drawables/ge_color.hpp"
#include "profiling/ge_profiler.hpp"
#include "renderer/ge_vertices_data.hpp"

using namespace GE;

namespace
{
  Vec3 GetNormal(u32 idx, const std::vector<Face>& faces, const std::vector<Vec3>& vertices)
  {
    GE_PROFILE;
    std::vector<std::pair<Vec3, f32>> normals; // normal, distance
    for (const auto& [f, c, n] : faces)
    {
      if (u64(f.x) == idx || u64(f.y) == idx || u64(f.z) == idx)
      {
        normals.emplace_back(n, c.Distance(vertices[idx]));
      }
    }

    f32 distance_sums = 0;
    for (const auto& [normal, dist] : normals)
      distance_sums += dist;
    for (auto& [normal, w] : normals)
      w = w / distance_sums;

    GE_ASSERT(!normals.empty(), "Not normal")

    const Vec3 normal =
      std::reduce(normals.begin(),
                  normals.end(),
                  std::pair<Vec3, f32>{},
                  [&](std::pair<Vec3, float> res,
                      const std::pair<Vec3, f32>& norm_weight) -> std::pair<Vec3, f32> {
                    return std::make_pair(res.first + norm_weight.first * norm_weight.second, 0.0f);
                  })
        .first;
    return normal;
  }

  auto ReadFacesAndVertices(std::string_view path)
  {
    GE_PROFILE;
    std::ifstream file{ std::string{ path } };
    if (!file.is_open())
    {
      GE_ERROR("File do not found!")
      throw std::runtime_error{ "File do not found" };
    }
    std::string line;
    std::vector<Vec3> vertices;
    std::vector<Face> faces;
    while (std::getline(file, line))
    {
      std::istringstream iss(line);
      char type = '\0';
      f64 x{};
      f64 y{};
      f64 z{};
      if (iss >> type >> x >> y >> z)
      {
        if (type == 'v')
        {
          vertices.emplace_back(static_cast<f32>(x), static_cast<f32>(y), static_cast<f32>(z));
        }
        else if (type == 'f')
        {
          const u32 i1 = static_cast<u32>(x) - 1;
          const u32 i2 = static_cast<u32>(y) - 1;
          const u32 i3 = static_cast<u32>(z) - 1;
          const IVec3 indices{ static_cast<i32>(i1), static_cast<i32>(i2), static_cast<i32>(i3) };

          const auto& v1 = vertices[i1];
          const auto& v2 = vertices[i2];
          const auto& v3 = vertices[i3];

          const auto e1 = v2 - v1;
          const auto e2 = v3 - v1;

          const auto normal = (e1.Cross(e2)).Normalize();
          const auto center = (v1 + v2 + v3) * (1.0f / 3.0f);

          faces.emplace_back(indices, center, normal);
        }
      }
    }

    return std::make_tuple(faces, vertices);
  }

  auto BuildVerticesAndIndicesData(std::string_view path)
  {
    GE_PROFILE;
    auto [faces, vertices] = ReadFacesAndVertices(path);

    const auto min_x = std::ranges::min(vertices, {}, &Vec3::x);
    const auto min_z = std::ranges::min(vertices, {}, &Vec3::z);
    const auto translate_fac = Vec3{ -min_x.x, 0, -min_z.z };
    for (Vec3& v : vertices)
    {
      v += translate_fac;
    }

    std::vector<u32> indices{};
    indices.reserve(faces.size() * 3);
    for (const IVec3 face : faces //
                              | std::views::transform([](auto&& f) { return f.indices; }))
    {
      indices.push_back(u32(face.x));
      indices.push_back(u32(face.y));
      indices.push_back(u32(face.z));
    }

    std::vector<Vec3> normals{};
    {
      GE_PROFILE_SECTION("Calculate normals");
      normals.resize(vertices.size());
      std::vector<u64> v_ids;
      for (u64 i = 0; i < vertices.size(); i++)
        v_ids.push_back(i);
      std::for_each(std::execution::par_unseq,
                    v_ids.begin(),
                    v_ids.end(),
                    [&](u64 idx) { normals.at(idx) = GetNormal(idx, faces, vertices); });
    }

    VerticesData vertices_data;
    {
      GE_PROFILE;
      auto color = Colors::WHITE.ToVec4();
      for (const u64 vtx_idx : std::views::iota(0u, vertices.size()))
      {
        vertices_data.PushVerticesData(
          { vertices.at(vtx_idx), Vec2{}, color, normals.at(vtx_idx) });
      }
    }

    return std::make_tuple(vertices_data, indices);
  }

  auto BuildDrawable(std::string_view path)
  {
    auto [vertices, indices] = BuildVerticesAndIndicesData(path);
    return Drawable{ vertices, indices };
  }
}

GE::Mesh::Mesh(std::string_view path) : m_drawable(BuildDrawable(path)) {}

const Drawable& Mesh::GetDrawable() const
{
  return m_drawable;
}
