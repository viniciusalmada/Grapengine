#include "drawables/ge_mesh.hpp"

#include "drawables/ge_color.hpp"
#include "profiling/ge_profiler.hpp"
#include "renderer/ge_vertices_data.hpp"

using namespace GE;

GE::Mesh::Mesh(std::string_view path)
{
  GE_PROFILE;

  std::ifstream file{ std::string{ path } };
  if (!file.is_open())
  {
    GE_ERROR("File do not found!")
    return;
  }
  std::string line;
  std::vector<Vec3> m_vertices;
  std::vector<Face> m_faces;
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
        m_vertices.emplace_back(static_cast<f32>(x), static_cast<f32>(y), static_cast<f32>(z));
      }
      else if (type == 'f')
      {
        const u32 i1 = static_cast<u32>(x) - 1;
        const u32 i2 = static_cast<u32>(y) - 1;
        const u32 i3 = static_cast<u32>(z) - 1;
        const IVec3 indices{ static_cast<i32>(i1), static_cast<i32>(i2), static_cast<i32>(i3) };

        const auto& v1 = m_vertices[i1];
        const auto& v2 = m_vertices[i2];
        const auto& v3 = m_vertices[i3];

        const auto e1 = v2 - v1;
        const auto e2 = v3 - v1;

        const auto normal = (e1.Cross(e2)).Normalize();
        const auto center = (v1 + v2 + v3) * (1.0f / 3.0f);

        m_faces.emplace_back(indices, center, normal);
      }
    }
  }

  GE_TRACE("Read {} vertices", m_vertices.size())
  GE_TRACE("Read {} faces", m_faces.size())

  const auto min_x = std::ranges::min(m_vertices, {}, &Vec3::x);
  const auto min_z = std::ranges::min(m_vertices, {}, &Vec3::z);
  const auto translate_fac = Vec3{ -min_x.x, 0, -min_z.z };
  for (Vec3& v : m_vertices)
  {
    v += translate_fac;
  }

  const Ptr<std::vector<u32>> indices = MakeRef<std::vector<u32>>();
  indices->reserve(m_faces.size() * 3);
  for (const IVec3 face : m_faces //
                            | std::views::transform([](auto&& f) { return f.indices; }))
  {
    indices->push_back(u32(face.x));
    indices->push_back(u32(face.y));
    indices->push_back(u32(face.z));
  }
  const std::set<u32> indices_set{ indices->begin(), indices->end() };

  auto get_normal = [&](u64 idx)
  {
    std::vector<std::pair<Vec3, f32>> normals; // normal, distance
    for (const auto& [f, c, n] : m_faces)
    {
      if (u64(f.x) == idx || u64(f.y) == idx || u64(f.z) == idx)
      {
        normals.emplace_back(n, c.Distance(m_vertices[idx]));
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
  };

  for (const u64 vtx_idx : std::views::iota(0u, m_vertices.size()))
  {
    const Vec3 normal = get_normal(vtx_idx);
    m_vertices_data.PushVerticesData({ m_vertices[vtx_idx], Vec2{}, m_color.ToVec4(), normal });
  }
}

Mesh::~Mesh() = default;

VerticesData Mesh::GetVerticesData(Color /*color*/) const
{
  return m_vertices_data;
}
const std::vector<u32>& Mesh::GetIndicesData() const
{
  return m_indices;
}
