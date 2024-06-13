#include "drawables/ge_mesh.hpp"

#include "drawables/ge_color.hpp"
#include "profiling/ge_profiler.hpp"
#include "renderer/ge_vertices_data.hpp"

using namespace GE;

GE::Mesh::Mesh(std::string_view path)
{
  GE_PROFILE;
  ReadFile(path);

  const auto min_x = std::ranges::min(m_vertices, {}, &Vec3::x);
  const auto min_z = std::ranges::min(m_vertices, {}, &Vec3::z);
  const auto translate_fac = Vec3{ -min_x.x, 0, -min_z.z };
  for (Vec3& v : m_vertices)
  {
    v += translate_fac;
  }

  m_indices.reserve(m_faces.size() * 3);
  for (const IVec3 face : m_faces //
                            | std::views::transform([](auto&& f) { return f.indices; }))
  {
    m_indices.push_back(u32(face.x));
    m_indices.push_back(u32(face.y));
    m_indices.push_back(u32(face.z));
  }

  {
    GE_PROFILE_SECTION("Calculate normals");
    m_normals.resize(m_vertices.size());
    std::vector<u64> v_ids;
    for (u64 i = 0; i < m_vertices.size(); i++)
      v_ids.push_back(i);
    std::for_each(std::execution::par_unseq,
                  v_ids.begin(),
                  v_ids.end(),
                  [&](u64 idx) { m_normals.at(idx) = GetNormal(idx); });
  }

  UpdateVerticesData();
}
void GE::Mesh::ReadFile(std::string_view path)
{
  GE_PROFILE;
  std::ifstream file{ std::string{ path } };
  if (!file.is_open())
  {
    GE_ERROR("File do not found!")
    return;
  }
  std::string line;
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
  GE_TRACE("Read {} faces", m_faces.size())
  GE_TRACE("Read {} vertices", m_vertices.size())
}

Mesh::~Mesh() = default;

VerticesData Mesh::GetVerticesData(Color color) const
{
  GE_PROFILE;
  if (color == m_color)
    return m_vertices_data;
  m_color = color;
  UpdateVerticesData();
  return m_vertices_data;
}
const std::vector<u32>& Mesh::GetIndicesData() const
{
  return m_indices;
}

Vec3 Mesh::GetNormal(u64 idx) const
{
  GE_PROFILE;
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
}

void Mesh::UpdateVerticesData() const
{
  GE_PROFILE;
  m_vertices_data.Clear();
  for (const u64 vtx_idx : std::views::iota(0u, m_vertices.size()))
  {
    m_vertices_data.PushVerticesData(
      { m_vertices.at(vtx_idx), Vec2{}, m_color.ToVec4(), m_normals.at(vtx_idx) });
  }
}
