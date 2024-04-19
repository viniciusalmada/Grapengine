#include "drawables/ge_cube.hpp"

#include "drawables/ge_drawing_object.hpp"
#include "math/ge_transformations.hpp"
#include "renderer/ge_ishader_program.hpp"
#include "renderer/ge_texture_2d.hpp"
#include "renderer/ge_vertices_data.hpp"
#include "renderer/shader_programs/ge_pos_tex_shader.hpp"

using namespace GE;

namespace
{
  auto GetCubeVerticesPositions(const Ref<const BufferLayout>& layout, Color color)
  {
    auto position = VerticesData::Make(layout);
    if (layout->HasNormal())
    {
      // clang-format off
    position->PushData(Vec3{ -0.5f, -0.5f, +0.5f  },Vec2{ 0.00f + 0 * 0.33f, 0.00f + 0 * 0.33f }, color.ToVec4(), Vec3{+0,+0,+1}.Normalize());// Front face
    position->PushData(Vec3{ +0.5f, -0.5f, +0.5f  },Vec2{ 0.34f + 0 * 0.33f, 0.00f + 0 * 0.33f }, color.ToVec4(), Vec3{+0,+0,+1}.Normalize());
    position->PushData(Vec3{ +0.5f, +0.5f, +0.5f  },Vec2{ 0.34f + 0 * 0.33f, 0.34f + 0 * 0.33f }, color.ToVec4(), Vec3{+0,+0,+1}.Normalize());
    position->PushData(Vec3{ -0.5f, +0.5f, +0.5f  },Vec2{ 0.00f + 0 * 0.33f, 0.34f + 0 * 0.33f }, color.ToVec4(), Vec3{+0,+0,+1}.Normalize());
    position->PushData(Vec3{ +0.5f, -0.5f, +0.5f  },Vec2{ 0.00f + 2 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4(), Vec3{+1,+0,+0}.Normalize());// Right face
    position->PushData(Vec3{ +0.5f, -0.5f, -0.5f  },Vec2{ 0.34f + 2 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4(), Vec3{+1,+0,+0}.Normalize());
    position->PushData(Vec3{ +0.5f, +0.5f, -0.5f  },Vec2{ 0.34f + 2 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4(), Vec3{+1,+0,+0}.Normalize());
    position->PushData(Vec3{ +0.5f, +0.5f, +0.5f  },Vec2{ 0.00f + 2 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4(), Vec3{+1,+0,+0}.Normalize());
    position->PushData(Vec3{ +0.5f, -0.5f, -0.5f  },Vec2{ 0.00f + 2 * 0.33f, 0.00f + 0 * 0.33f }, color.ToVec4(), Vec3{+0,+0,-1}.Normalize());// Back face
    position->PushData(Vec3{ -0.5f, -0.5f, -0.5f  },Vec2{ 0.34f + 2 * 0.33f, 0.00f + 0 * 0.33f }, color.ToVec4(), Vec3{+0,+0,-1}.Normalize());
    position->PushData(Vec3{ -0.5f, +0.5f, -0.5f  },Vec2{ 0.34f + 2 * 0.33f, 0.34f + 0 * 0.33f }, color.ToVec4(), Vec3{+0,+0,-1}.Normalize());
    position->PushData(Vec3{ +0.5f, +0.5f, -0.5f  },Vec2{ 0.00f + 2 * 0.33f, 0.34f + 0 * 0.33f }, color.ToVec4(), Vec3{+0,+0,-1}.Normalize());
    position->PushData(Vec3{ -0.5f, -0.5f, -0.5f  },Vec2{ 0.00f + 1 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4(), Vec3{-1,+0,+0}.Normalize());// Left face
    position->PushData(Vec3{ -0.5f, -0.5f, +0.5f  },Vec2{ 0.34f + 1 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4(), Vec3{-1,+0,+0}.Normalize());
    position->PushData(Vec3{ -0.5f, +0.5f, +0.5f  },Vec2{ 0.34f + 1 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4(), Vec3{-1,+0,+0}.Normalize());
    position->PushData(Vec3{ -0.5f, +0.5f, -0.5f  },Vec2{ 0.00f + 1 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4(), Vec3{-1,+0,+0}.Normalize());
    position->PushData(Vec3{ -0.5f, +0.5f, +0.5f  },Vec2{ 0.00f + 0 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4(), Vec3{+0,+1,+0}.Normalize());// Top face
    position->PushData(Vec3{ +0.5f, +0.5f, +0.5f  },Vec2{ 0.34f + 0 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4(), Vec3{+0,+1,+0}.Normalize());
    position->PushData(Vec3{ +0.5f, +0.5f, -0.5f  },Vec2{ 0.34f + 0 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4(), Vec3{+0,+1,+0}.Normalize());
    position->PushData(Vec3{ -0.5f, +0.5f, -0.5f  },Vec2{ 0.00f + 0 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4(), Vec3{+0,+1,+0}.Normalize());
    position->PushData(Vec3{ -0.5f, -0.5f, -0.5f  },Vec2{ 0.00f + 0 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4(), Vec3{+0,-1,+0}.Normalize());// Bottom face
    position->PushData(Vec3{ +0.5f, -0.5f, -0.5f  },Vec2{ 0.34f + 0 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4(), Vec3{+0,-1,+0}.Normalize());
    position->PushData(Vec3{ +0.5f, -0.5f, +0.5f  },Vec2{ 0.34f + 0 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4(), Vec3{+0,-1,+0}.Normalize());
    position->PushData(Vec3{ -0.5f, -0.5f, +0.5f  },Vec2{ 0.00f + 0 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4(), Vec3{+0,-1,+0}.Normalize());
      // clang-format on
    }
    else
    {
      // clang-format off
    position->PushData(Vec3{ -0.5f, -0.5f, +0.5f  },Vec2{ 0.00f + 0 * 0.33f, 0.00f + 0 * 0.33f }, color.ToVec4());// Front face
    position->PushData(Vec3{ +0.5f, -0.5f, +0.5f  },Vec2{ 0.34f + 0 * 0.33f, 0.00f + 0 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ +0.5f, +0.5f, +0.5f  },Vec2{ 0.34f + 0 * 0.33f, 0.34f + 0 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ -0.5f, +0.5f, +0.5f  },Vec2{ 0.00f + 0 * 0.33f, 0.34f + 0 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ +0.5f, -0.5f, +0.5f  },Vec2{ 0.00f + 2 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4());// Right face
    position->PushData(Vec3{ +0.5f, -0.5f, -0.5f  },Vec2{ 0.34f + 2 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ +0.5f, +0.5f, -0.5f  },Vec2{ 0.34f + 2 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ +0.5f, +0.5f, +0.5f  },Vec2{ 0.00f + 2 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ +0.5f, -0.5f, -0.5f  },Vec2{ 0.00f + 2 * 0.33f, 0.00f + 0 * 0.33f }, color.ToVec4());// Back face
    position->PushData(Vec3{ -0.5f, -0.5f, -0.5f  },Vec2{ 0.34f + 2 * 0.33f, 0.00f + 0 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ -0.5f, +0.5f, -0.5f  },Vec2{ 0.34f + 2 * 0.33f, 0.34f + 0 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ +0.5f, +0.5f, -0.5f  },Vec2{ 0.00f + 2 * 0.33f, 0.34f + 0 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ -0.5f, -0.5f, -0.5f  },Vec2{ 0.00f + 1 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4());// Left face
    position->PushData(Vec3{ -0.5f, -0.5f, +0.5f  },Vec2{ 0.34f + 1 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ -0.5f, +0.5f, +0.5f  },Vec2{ 0.34f + 1 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ -0.5f, +0.5f, -0.5f  },Vec2{ 0.00f + 1 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ -0.5f, +0.5f, +0.5f  },Vec2{ 0.00f + 0 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4());// Top face
    position->PushData(Vec3{ +0.5f, +0.5f, +0.5f  },Vec2{ 0.34f + 0 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ +0.5f, +0.5f, -0.5f  },Vec2{ 0.34f + 0 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ -0.5f, +0.5f, -0.5f  },Vec2{ 0.00f + 0 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ -0.5f, -0.5f, -0.5f  },Vec2{ 0.00f + 0 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4());// Bottom face
    position->PushData(Vec3{ +0.5f, -0.5f, -0.5f  },Vec2{ 0.34f + 0 * 0.33f, 0.00f + 1 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ +0.5f, -0.5f, +0.5f  },Vec2{ 0.34f + 0 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4());
    position->PushData(Vec3{ -0.5f, -0.5f, +0.5f  },Vec2{ 0.00f + 0 * 0.33f, 0.34f + 1 * 0.33f }, color.ToVec4());
      // clang-format on
    }
    return position;
  }
}

Cube::Cube(Color color, const Ref<IShaderProgram>& shader, Ref<Texture2D> texture) :
    Drawable(shader)
{
  m_shader = shader;
  m_color = color;
  m_texture = std::move(texture);
  auto layout = shader->GetLayout();

  const auto positions = GetCubeVerticesPositions(layout, color);
  Ref<std::vector<u32>> indices = MakeRef<std::vector<u32>>(std::initializer_list<u32>{
    0,  1,  2,  2,  3,  0,  // Front face
    4,  5,  6,  6,  7,  4,  // Right face
    8,  9,  10, 10, 11, 8,  // Back face
    12, 13, 14, 14, 15, 12, // Left face
    16, 17, 18, 18, 19, 16, // Top face
    20, 21, 22, 22, 23, 20, // Bottom face
  });

  m_draw_primitive = MakeRef<DrawingObject>(positions, indices);
}
void Cube::Draw() const
{
  m_shader->Activate();
  m_texture->Bind(0);
  m_texture->Bind(0);
  m_shader->UpdateModelMatrix(m_translate_mat * m_scale_mat);
  m_shader->UpdateTexture(0);
  //  m_draw_primitive->Draw();
}

void GE::Cube::SetScale(f32 x, f32 y, f32 z)
{
  m_scale_mat = Transform::Scale(x, y, z);
}

void GE::Cube::SetTranslate(f32 x, f32 y, f32 z)
{
  m_translate_mat = Transform::Translate(x, y, z);
}

Ref<Cube> GE::Cube::Make(Color color, const Ref<IShaderProgram>& shader, Ref<Texture2D> texture)
{
  return MakeRef<Cube>(color, shader, std::move(texture));
}

void GE::Cube::SetTranslate(Vec3 xyz)
{
  SetTranslate(xyz.x, xyz.y, xyz.z);
}

void GE::Cube::SetColor(Color color)
{
  m_color = color;
  const auto positions = GetCubeVerticesPositions(m_shader->GetLayout(), color);
  m_draw_primitive->UpdateVerticesData(positions);
}

Ref<DrawingObject> GE::Cube::GetVAO() const
{
  return m_draw_primitive;
}

Mat4 GE::Cube::GetModelMatrix() const
{
  return m_translate_mat * m_scale_mat;
}

Cube::~Cube() = default;
