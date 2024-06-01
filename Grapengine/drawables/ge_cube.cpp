#include "drawables/ge_cube.hpp"

#include "math/ge_transformations.hpp"
#include "renderer/ge_vertices_data.hpp"
#include "renderer/shader_programs/ge_pos_tex_shader.hpp"

using namespace GE;

namespace
{
  constexpr auto HALF = 0.5f;
  constexpr auto THIRD = 1.0f / 3.0f;

  auto& GetIndices()
  {
    // NOLINTBEGIN(*-magic-numbers)
    static const std::vector<u32> indices{
      0,  1,  2,  2,  3,  0,  // Front face
      4,  5,  6,  6,  7,  4,  // Right face
      8,  9,  10, 10, 11, 8,  // Back face
      12, 13, 14, 14, 15, 12, // Left face
      16, 17, 18, 18, 19, 16, // Top face
      20, 21, 22, 22, 23, 20, // Bottom face
    };
    // NOLINTEND(*-magic-numbers)
    return indices;
  }

  VerticesData GetCubeVerticesPositions(Color color)
  {
    VerticesData position{};
    // clang-format off
    position.PushVerticesData({Vec3{ -HALF, -HALF, +HALF  },Vec2{ 0.00f + 0 * THIRD, 0.00f + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,+1}.Normalize()});// Front face
    position.PushVerticesData({Vec3{ +HALF, -HALF, +HALF  },Vec2{ THIRD + 0 * THIRD, 0.00f + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,+1}.Normalize()});
    position.PushVerticesData({Vec3{ +HALF, +HALF, +HALF  },Vec2{ THIRD + 0 * THIRD, THIRD + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,+1}.Normalize()});
    position.PushVerticesData({Vec3{ -HALF, +HALF, +HALF  },Vec2{ 0.00f + 0 * THIRD, THIRD + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,+1}.Normalize()});
    position.PushVerticesData({Vec3{ +HALF, -HALF, +HALF  },Vec2{ 0.00f + 2 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{+1,+0,+0}.Normalize()});// Right face
    position.PushVerticesData({Vec3{ +HALF, -HALF, -HALF  },Vec2{ THIRD + 2 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{+1,+0,+0}.Normalize()});
    position.PushVerticesData({Vec3{ +HALF, +HALF, -HALF  },Vec2{ THIRD + 2 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{+1,+0,+0}.Normalize()});
    position.PushVerticesData({Vec3{ +HALF, +HALF, +HALF  },Vec2{ 0.00f + 2 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{+1,+0,+0}.Normalize()});
    position.PushVerticesData({Vec3{ +HALF, -HALF, -HALF  },Vec2{ 0.00f + 2 * THIRD, 0.00f + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,-1}.Normalize()});// Back face
    position.PushVerticesData({Vec3{ -HALF, -HALF, -HALF  },Vec2{ THIRD + 2 * THIRD, 0.00f + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,-1}.Normalize()});
    position.PushVerticesData({Vec3{ -HALF, +HALF, -HALF  },Vec2{ THIRD + 2 * THIRD, THIRD + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,-1}.Normalize()});
    position.PushVerticesData({Vec3{ +HALF, +HALF, -HALF  },Vec2{ 0.00f + 2 * THIRD, THIRD + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,-1}.Normalize()});
    position.PushVerticesData({Vec3{ -HALF, -HALF, -HALF  },Vec2{ 0.00f + 1 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{-1,+0,+0}.Normalize()});// Left face
    position.PushVerticesData({Vec3{ -HALF, -HALF, +HALF  },Vec2{ THIRD + 1 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{-1,+0,+0}.Normalize()});
    position.PushVerticesData({Vec3{ -HALF, +HALF, +HALF  },Vec2{ THIRD + 1 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{-1,+0,+0}.Normalize()});
    position.PushVerticesData({Vec3{ -HALF, +HALF, -HALF  },Vec2{ 0.00f + 1 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{-1,+0,+0}.Normalize()});
    position.PushVerticesData({Vec3{ -HALF, +HALF, +HALF  },Vec2{ 0.00f + 0 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{+0,+1,+0}.Normalize()});// Top face
    position.PushVerticesData({Vec3{ +HALF, +HALF, +HALF  },Vec2{ THIRD + 0 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{+0,+1,+0}.Normalize()});
    position.PushVerticesData({Vec3{ +HALF, +HALF, -HALF  },Vec2{ THIRD + 0 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{+0,+1,+0}.Normalize()});
    position.PushVerticesData({Vec3{ -HALF, +HALF, -HALF  },Vec2{ 0.00f + 0 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{+0,+1,+0}.Normalize()});
    position.PushVerticesData({Vec3{ -HALF, -HALF, -HALF  },Vec2{ 0.00f + 0 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{+0,-1,+0}.Normalize()});// Bottom face
    position.PushVerticesData({Vec3{ +HALF, -HALF, -HALF  },Vec2{ THIRD + 0 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{+0,-1,+0}.Normalize()});
    position.PushVerticesData({Vec3{ +HALF, -HALF, +HALF  },Vec2{ THIRD + 0 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{+0,-1,+0}.Normalize()});
    position.PushVerticesData({Vec3{ -HALF, -HALF, +HALF  },Vec2{ 0.00f + 0 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{+0,-1,+0}.Normalize()});
    // clang-format on
    return position;
  }
}

//-------------------------------------------------------------------------
Cube::Cube(Color color) : m_color(color) {}

VerticesData Cube::GetVerticesData() const
{
  VerticesData vd = GetCubeVerticesPositions(m_color);
  return vd;
}

const std::vector<u32>& Cube::GetIndicesData() const
{
  return GetIndices();
}
