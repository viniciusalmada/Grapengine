#include "drawables/ge_cube.hpp"

#include <drawables/ge_draw_primitive.hpp>
#include <renderer/ge_ishader_program.hpp>
#include <renderer/ge_renderer.hpp>
#include <renderer/ge_shaders_library.hpp>
#include <renderer/ge_vertices_data.hpp>

using namespace GE;

// clang-format off
  // X - left to right axis
  // Y - bottom to top axis
  // Z - near to far axis
  float vertices[] = {
    // Front face - 2
    -0.5, -0.5,  +0.5, 0.00 + 0 * 0.33, 0.00 + 0 * 0.33,
    +0.5, -0.5,  +0.5, 0.34 + 0 * 0.33, 0.00 + 0 * 0.33,
    +0.5, +0.5,  +0.5, 0.34 + 0 * 0.33, 0.34 + 0 * 0.33,
    -0.5, +0.5,  +0.5, 0.00 + 0 * 0.33, 0.34 + 0 * 0.33,

    // Right face - 1
    +0.5, -0.5,  +0.5, 0.00 + 2 * 0.33, 0.00 + 1 * 0.33,
    +0.5, -0.5,  -0.5, 0.34 + 2 * 0.33, 0.00 + 1 * 0.33,
    +0.5, +0.5,  -0.5, 0.34 + 2 * 0.33, 0.34 + 1 * 0.33,
    +0.5, +0.5,  +0.5, 0.00 + 2 * 0.33, 0.34 + 1 * 0.33,

    // Back face - 5
    +0.5, -0.5,  -0.5, 0.00 + 2 * 0.33, 0.00 + 0 * 0.33,
    -0.5, -0.5,  -0.5, 0.34 + 2 * 0.33, 0.00 + 0 * 0.33,
    -0.5, +0.5,  -0.5, 0.34 + 2 * 0.33, 0.34 + 0 * 0.33,
    +0.5, +0.5,  -0.5, 0.00 + 2 * 0.33, 0.34 + 0 * 0.33,

    // Left face - 6
    -0.5, -0.5,  -0.5, 0.00 + 1 * 0.33, 0.00 + 1 * 0.33,
    -0.5, -0.5,  +0.5, 0.34 + 1 * 0.33, 0.00 + 1 * 0.33,
    -0.5, +0.5,  +0.5, 0.34 + 1 * 0.33, 0.34 + 1 * 0.33,
    -0.5, +0.5,  -0.5, 0.00 + 1 * 0.33, 0.34 + 1 * 0.33,

    // Top face - 3
    -0.5, +0.5,  +0.5, 0.00 + 0 * 0.33, 0.00 + 1 * 0.33,
    +0.5, +0.5,  +0.5, 0.34 + 0 * 0.33, 0.00 + 1 * 0.33,
    +0.5, +0.5,  -0.5, 0.34 + 0 * 0.33, 0.34 + 1 * 0.33,
    -0.5, +0.5,  -0.5, 0.00 + 0 * 0.33, 0.34 + 1 * 0.33,

    // Bottom face - 4
    -0.5, -0.5,  -0.5, 0.00 + 0 * 0.33, 0.00 + 1 * 0.33,
    +0.5, -0.5,  -0.5, 0.34 + 0 * 0.33, 0.00 + 1 * 0.33,
    +0.5, -0.5,  +0.5, 0.34 + 0 * 0.33, 0.34 + 1 * 0.33,
    -0.5, -0.5,  +0.5, 0.00 + 0 * 0.33, 0.34 + 1 * 0.33,
  };
// clang-format on

struct Cube::Impl
{
  float position_x = 0;
  float position_y = 0;
  float position_z = 0;
  float height = 0;
  Color color{};
  Ref<DrawPrimitive> draw_primitive;
  Shaders shader;
};

Cube::Cube(float x, float y, float z, Shaders shader) : Drawable(shader), m_pimpl(MakeScope<Impl>())
{
  m_pimpl->shader = shader;
  auto layout = MakeRef<BufferLayout>(std::initializer_list<BufferElem>{
    BufferElem{ "in_position", ShaderDataType::Float3, sizeof(float) * 3, 0, false },
    BufferElem{ "in_texture_coord",
                ShaderDataType::Float2,
                sizeof(float) * 2,
                sizeof(float) * 3,
                false } });

  auto position = MakeRef<VerticesData>(layout);
  {
    position->PushData(Vec3{ -0.5f + x, -0.5f + y, +0.5f + z },
                       Vec2{ 0.00 + 0 * 0.33, 0.00 + 0 * 0.33 });
    position->PushData(Vec3{ +0.5f + x, -0.5f + y, +0.5f + z },
                       Vec2{ 0.34 + 0 * 0.33, 0.00 + 0 * 0.33 });
    position->PushData(Vec3{ +0.5f + x, +0.5f + y, +0.5f + z },
                       Vec2{ 0.34 + 0 * 0.33, 0.34 + 0 * 0.33 });
    position->PushData(Vec3{ -0.5f + x, +0.5f + y, +0.5f + z },
                       Vec2{ 0.00 + 0 * 0.33, 0.34 + 0 * 0.33 });
    position->PushData(Vec3{ +0.5f + x, -0.5f + y, +0.5f + z },
                       Vec2{ 0.00 + 2 * 0.33, 0.00 + 1 * 0.33 });
    position->PushData(Vec3{ +0.5f + x, -0.5f + y, -0.5f + z },
                       Vec2{ 0.34 + 2 * 0.33, 0.00 + 1 * 0.33 });
    position->PushData(Vec3{ +0.5f + x, +0.5f + y, -0.5f + z },
                       Vec2{ 0.34 + 2 * 0.33, 0.34 + 1 * 0.33 });
    position->PushData(Vec3{ +0.5f + x, +0.5f + y, +0.5f + z },
                       Vec2{ 0.00 + 2 * 0.33, 0.34 + 1 * 0.33 });
    position->PushData(Vec3{ +0.5f + x, -0.5f + y, -0.5f + z },
                       Vec2{ 0.00 + 2 * 0.33, 0.00 + 0 * 0.33 });
    position->PushData(Vec3{ -0.5f + x, -0.5f + y, -0.5f + z },
                       Vec2{ 0.34 + 2 * 0.33, 0.00 + 0 * 0.33 });
    position->PushData(Vec3{ -0.5f + x, +0.5f + y, -0.5f + z },
                       Vec2{ 0.34 + 2 * 0.33, 0.34 + 0 * 0.33 });
    position->PushData(Vec3{ +0.5f + x, +0.5f + y, -0.5f + z },
                       Vec2{ 0.00 + 2 * 0.33, 0.34 + 0 * 0.33 });
    position->PushData(Vec3{ -0.5f + x, -0.5f + y, -0.5f + z },
                       Vec2{ 0.00 + 1 * 0.33, 0.00 + 1 * 0.33 });
    position->PushData(Vec3{ -0.5f + x, -0.5f + y, +0.5f + z },
                       Vec2{ 0.34 + 1 * 0.33, 0.00 + 1 * 0.33 });
    position->PushData(Vec3{ -0.5f + x, +0.5f + y, +0.5f + z },
                       Vec2{ 0.34 + 1 * 0.33, 0.34 + 1 * 0.33 });
    position->PushData(Vec3{ -0.5f + x, +0.5f + y, -0.5f + z },
                       Vec2{ 0.00 + 1 * 0.33, 0.34 + 1 * 0.33 });
    position->PushData(Vec3{ -0.5f + x, +0.5f + y, +0.5f + z },
                       Vec2{ 0.00 + 0 * 0.33, 0.00 + 1 * 0.33 });
    position->PushData(Vec3{ +0.5f + x, +0.5f + y, +0.5f + z },
                       Vec2{ 0.34 + 0 * 0.33, 0.00 + 1 * 0.33 });
    position->PushData(Vec3{ +0.5f + x, +0.5f + y, -0.5f + z },
                       Vec2{ 0.34 + 0 * 0.33, 0.34 + 1 * 0.33 });
    position->PushData(Vec3{ -0.5f + x, +0.5f + y, -0.5f + z },
                       Vec2{ 0.00 + 0 * 0.33, 0.34 + 1 * 0.33 });
    position->PushData(Vec3{ -0.5f + x, -0.5f + y, -0.5f + z },
                       Vec2{ 0.00 + 0 * 0.33, 0.00 + 1 * 0.33 });
    position->PushData(Vec3{ +0.5f + x, -0.5f + y, -0.5f + z },
                       Vec2{ 0.34 + 0 * 0.33, 0.00 + 1 * 0.33 });
    position->PushData(Vec3{ +0.5f + x, -0.5f + y, +0.5f + z },
                       Vec2{ 0.34 + 0 * 0.33, 0.34 + 1 * 0.33 });
    position->PushData(Vec3{ -0.5f + x, -0.5f + y, +0.5f + z },
                       Vec2{ 0.00 + 0 * 0.33, 0.34 + 1 * 0.33 });
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
  ShadersLibrary::Get().Activate(m_pimpl->shader);

  m_pimpl->draw_primitive->Draw();
}

Cube::~Cube() = default;
