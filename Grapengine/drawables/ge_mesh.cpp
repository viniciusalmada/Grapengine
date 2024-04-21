#include "drawables/ge_mesh.hpp"

#include "drawables/ge_color.hpp"
#include "drawables/ge_cube.hpp"
#include "drawables/ge_cylinder.hpp"
#include "drawables/ge_drawing_object.hpp"
#include "renderer/ge_vertices_data.hpp"

using namespace GE;

namespace
{
  constexpr auto NORMAL_RADIUS = 0.01f;
  constexpr auto NORMAL_HEIGHT = 0.05f;
  constexpr auto TWO = 2.0f;
}

GE::Mesh::Mesh(std::string_view path, const GE::Ref<GE::IShaderProgram>& shader) :
    Drawable(shader), m_shader(shader)
{

  m_texture = Texture2D::Make();

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

  GE_TRACE("Read {} vertices", m_vertices.size())
  GE_TRACE("Read {} faces", m_faces.size())

  const auto max_x = std::ranges::max(m_vertices, {}, &Vec3::x);
  const auto min_x = std::ranges::min(m_vertices, {}, &Vec3::x);
  const auto max_y = std::ranges::max(m_vertices, {}, &Vec3::y);
  const auto min_y = std::ranges::min(m_vertices, {}, &Vec3::y);
  const auto max_z = std::ranges::max(m_vertices, {}, &Vec3::z);
  const auto min_z = std::ranges::min(m_vertices, {}, &Vec3::z);
  const auto translate_fac = Vec3{ -min_x.x, 0, -min_z.z };
  for (Vec3& v : m_vertices)
  {
    v += translate_fac;
  }
  for (auto& face : m_faces)
  {
    m_normals.push_back(Cylinder::Make(m_shader,
                                       face.center + translate_fac,
                                       NORMAL_RADIUS,
                                       face.normal,
                                       NORMAL_HEIGHT,
                                       Colors::RED,
                                       m_texture));
  }

  const Ref<std::vector<u32>> indices = MakeRef<std::vector<u32>>();
  indices->reserve(m_faces.size() * 3);
  for (const IVec3 face : m_faces //
                            | std::views::transform([](auto&& f) { return f.indices; }))
  {
    indices->push_back(u32(face.x));
    indices->push_back(u32(face.y));
    indices->push_back(u32(face.z));
  }
  const std::set<u32> indices_set{ indices->begin(), indices->end() };

  const Ref<VerticesData> vertices_data = MakeRef<VerticesData>(shader->GetLayout());

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
    vertices_data->PushData(m_vertices[vtx_idx], Vec2{}, m_color.ToVec4(), normal);
  }

  m_draw_primitive = MakeRef<DrawingObject>(vertices_data, indices);

  const Color BBOX_COLOR{ 0xFFFFFF33 };
  m_bbox = Cube::Make(BBOX_COLOR, shader, m_texture);
  m_bbox->SetTranslate(min_x.x + (max_x.x - min_x.x) / TWO,
                       min_y.y + (max_y.y - min_y.y) / TWO,
                       min_z.z + (max_z.z - min_z.z) / TWO);
  m_bbox->SetScale(max_x.x - min_x.x, max_y.y - min_y.y, max_z.z - min_z.z);
}

Mesh::~Mesh() = default;

void GE::Mesh::Draw() const
{
  m_texture->Bind(0);
  m_shader->UpdateTexture(0);
  m_shader->UpdateModelMatrix(Mat4{});
  //  m_draw_primitive->Draw();

  //  Renderer::SetWireframeRenderMode(false);
  //  for (auto& n : m_normals)
  //    n->Draw();
  //  m_bbox->Draw();
}
