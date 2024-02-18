#include "drawables/ge_cube.hpp"

#include <drawables/ge_draw_primitive.hpp>
#include <math/ge_transformations.hpp>
#include <renderer/ge_ishader_program.hpp>
#include <renderer/ge_renderer.hpp>
#include <renderer/ge_shaders_library.hpp>
#include <renderer/ge_texture_2d.hpp>
#include <renderer/ge_vertices_data.hpp>
#include <renderer/shader_programs/ge_pos_tex_shader.hpp>
#include <utility>

using namespace GE;

// clang-format off
  // X - left to right axis
  // Y - bottom to top axis
  // Z - near to far axis
  f32 vertices[] = {
    -0.5f, -0.5f,  +0.5f, 0.00f + 0 * 0.33f, 0.00f + 0 * 0.33f, // Front face - 2
    +0.5f, -0.5f,  +0.5f, 0.34f + 0 * 0.33f, 0.00f + 0 * 0.33f,
    +0.5f, +0.5f,  +0.5f, 0.34f + 0 * 0.33f, 0.34f + 0 * 0.33f,
    -0.5f, +0.5f,  +0.5f, 0.00f + 0 * 0.33f, 0.34f + 0 * 0.33f,
    +0.5f, -0.5f,  +0.5f, 0.00f + 2 * 0.33f, 0.00f + 1 * 0.33f, // Right face - 1
    +0.5f, -0.5f,  -0.5f, 0.34f + 2 * 0.33f, 0.00f + 1 * 0.33f,
    +0.5f, +0.5f,  -0.5f, 0.34f + 2 * 0.33f, 0.34f + 1 * 0.33f,
    +0.5f, +0.5f,  +0.5f, 0.00f + 2 * 0.33f, 0.34f + 1 * 0.33f,
    +0.5f, -0.5f,  -0.5f, 0.00f + 2 * 0.33f, 0.00f + 0 * 0.33f, // Back face - 5
    -0.5f, -0.5f,  -0.5f, 0.34f + 2 * 0.33f, 0.00f + 0 * 0.33f,
    -0.5f, +0.5f,  -0.5f, 0.34f + 2 * 0.33f, 0.34f + 0 * 0.33f,
    +0.5f, +0.5f,  -0.5f, 0.00f + 2 * 0.33f, 0.34f + 0 * 0.33f,
    -0.5f, -0.5f,  -0.5f, 0.00f + 1 * 0.33f, 0.00f + 1 * 0.33f, // Left face - 6
    -0.5f, -0.5f,  +0.5f, 0.34f + 1 * 0.33f, 0.00f + 1 * 0.33f,
    -0.5f, +0.5f,  +0.5f, 0.34f + 1 * 0.33f, 0.34f + 1 * 0.33f,
    -0.5f, +0.5f,  -0.5f, 0.00f + 1 * 0.33f, 0.34f + 1 * 0.33f,
    -0.5f, +0.5f,  +0.5f, 0.00f + 0 * 0.33f, 0.00f + 1 * 0.33f, // Top face - 3
    +0.5f, +0.5f,  +0.5f, 0.34f + 0 * 0.33f, 0.00f + 1 * 0.33f,
    +0.5f, +0.5f,  -0.5f, 0.34f + 0 * 0.33f, 0.34f + 1 * 0.33f,
    -0.5f, +0.5f,  -0.5f, 0.00f + 0 * 0.33f, 0.34f + 1 * 0.33f,
    -0.5f, -0.5f,  -0.5f, 0.00f + 0 * 0.33f, 0.00f + 1 * 0.33f, // Bottom face - 4
    +0.5f, -0.5f,  -0.5f, 0.34f + 0 * 0.33f, 0.00f + 1 * 0.33f,
    +0.5f, -0.5f,  +0.5f, 0.34f + 0 * 0.33f, 0.34f + 1 * 0.33f,
    -0.5f, -0.5f,  +0.5f, 0.00f + 0 * 0.33f, 0.34f + 1 * 0.33f,
  };
// clang-format on

struct Cube::Impl
{
  f32 position_x = 0;
  f32 position_y = 0;
  f32 position_z = 0;
  f32 height = 0;
  Color color{ 0 };
  Ref<DrawPrimitive> draw_primitive;
  Shaders shader;
  Mat4 scale_mat{};
  Mat4 translate_mat{};
  Ref<Texture2D> texture;
};

Cube::Cube(Color color, Shaders shader, Ref<Texture2D> texture) :
    Drawable(shader), m_pimpl(MakeScope<Impl>())
{
  m_pimpl->shader = shader;
  m_pimpl->color = color;
  m_pimpl->texture = std::move(texture);
  auto layout = ShadersLibrary::Get().GetLayout(shader);

  auto position = MakeRef<VerticesData>(layout);
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

  Ref<std::vector<u32>> indices = MakeRef<std::vector<u32>>(std::initializer_list<u32>{
    0,  1,  2,  2,  3,  0,  // Front face
    4,  5,  6,  6,  7,  4,  // Right face
    8,  9,  10, 10, 11, 8,  // Back face
    12, 13, 14, 14, 15, 12, // Left face
    16, 17, 18, 18, 19, 16, // Top face
    20, 21, 22, 22, 23, 20, // Bottom face
  });

  m_pimpl->draw_primitive = MakeRef<DrawPrimitive>(position, indices);
}
void Cube::Draw() const
{
  m_pimpl->texture->Bind(0);
  ShadersLibrary::Get().Activate(m_pimpl->shader);
  auto shader =
    std::static_pointer_cast<PosAndTex2DShader>(ShadersLibrary::Get().GetShader(m_pimpl->shader));
  shader->UpdateModelMatrix(m_pimpl->translate_mat * m_pimpl->scale_mat);
  shader->UpdateTexture(0);
  m_pimpl->draw_primitive->Draw();
}

void GE::Cube::SetScale(f32 x, f32 y, f32 z) const
{
  m_pimpl->scale_mat = Transform::Scale(x, y, z);
}

void GE::Cube::SetTranslate(f32 x, f32 y, f32 z) const
{
  m_pimpl->translate_mat = Transform::Translate(x, y, z);
}

Cube::~Cube() = default;
