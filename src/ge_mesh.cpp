#include "drawables/ge_mesh.hpp"

#include "drawables/ge_color.hpp"
#include "drawables/ge_cube.hpp"
#include "drawables/ge_draw_primitive.hpp"
#include "renderer/ge_vertices_data.hpp"

using namespace GE;

struct Mesh::Impl
{
  Color color = Colors::BLUE;
  Ref<DrawPrimitive> draw_primitive;
  Ref<Cube> bbox;
  Ref<IShaderProgram> shader;
  Ref<Texture2D> texture;
  Mat4 rotate_mat;
};

GE::Mesh::Mesh(std::string_view path, const GE::Ref<GE::IShaderProgram>& shader) :
    Drawable(shader), m_pimpl(MakeScope<Impl>())
{
  m_pimpl->shader = shader;
  m_pimpl->texture = Texture2D::Make();

  std::vector<Vec3> vertices;
  std::vector<IVec3> faces;

  std::ifstream file{ std::string{ path } };
  if (!file.is_open())
  {
    GE_ERROR("File do not found!");
    return;
  }
  std::string line;
  while (std::getline(file, line))
  {
    std::istringstream iss(line);
    char type;
    f64 x, y, z;
    if (iss >> type >> x >> y >> z)
    {
      if (type == 'v')
      {
        vertices.emplace_back(static_cast<f32>(x), static_cast<f32>(y), static_cast<f32>(z));
      }
      else if (type == 'f')
      {
        faces.emplace_back(static_cast<i32>(x) - 1,
                           static_cast<i32>(y) - 1,
                           static_cast<i32>(z) - 1);
      }
    }
  }

  GE_TRACE("Read {} vertices", vertices.size())
  GE_TRACE("Read {} faces", faces.size());

  const auto max_x = std::ranges::max(vertices, {}, &Vec3::x);
  const auto min_x = std::ranges::min(vertices, {}, &Vec3::x);
  const auto max_y = std::ranges::max(vertices, {}, &Vec3::y);
  const auto min_y = std::ranges::min(vertices, {}, &Vec3::y);
  const auto max_z = std::ranges::max(vertices, {}, &Vec3::z);
  const auto min_z = std::ranges::min(vertices, {}, &Vec3::z);
  for (Vec3& v : vertices)
  {
    v += Vec3(-min_x.x, 0, -min_z.z);
  }

  Ref<VerticesData> vertices_data = MakeRef<VerticesData>(shader->GetLayout());
  for (const auto& vtx : vertices)
    vertices_data->PushData(vtx, Vec2{}, m_pimpl->color.ToVec4());
  Ref<std::vector<u32>> indices = MakeRef<std::vector<u32>>();
  indices->reserve(faces.size() * 3);
  for (const auto& face : faces)
  {
    indices->push_back((u32)face.x);
    indices->push_back((u32)face.y);
    indices->push_back((u32)face.z);
  }

  m_pimpl->draw_primitive = MakeRef<DrawPrimitive>(vertices_data, indices);

  m_pimpl->bbox = Cube::Make(Color(0xFFFFFF33), shader, m_pimpl->texture);
  m_pimpl->bbox->SetTranslate(min_x.x + (max_x.x - min_x.x) / 2.0f,
                              min_y.y + (max_y.y - min_y.y) / 2.0f,
                              min_z.z + (max_z.z - min_z.z) / 2.0f);
  m_pimpl->bbox->SetScale(max_x.x - min_x.x, max_y.y - min_y.y, max_z.z - min_z.z);
}

Mesh::~Mesh() = default;

void GE::Mesh::Draw() const
{
  m_pimpl->texture->Bind(0);
  m_pimpl->shader->UpdateTexture(0);
  m_pimpl->draw_primitive->Draw();
  //  m_pimpl->bbox->Draw();
}