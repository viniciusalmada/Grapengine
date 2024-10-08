#include "drawables/ge_cube.hpp"

#include "math/ge_transformations.hpp"
#include "profiling/ge_profiler.hpp"
#include "renderer/ge_vertices_data.hpp"

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

  VerticesData GetCubeVerticesPositions()
  {
    const Color& color = Colors::WHITE;
    VerticesData position{};
    // clang-format off
    position.PushVerticesData({Vec3{ -HALF, -HALF, +HALF  },Vec2{ 0.00f + 0 * THIRD, 0.00f + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,+1}.Normalize(), Texture2D::EMPTY_TEX_SLOT});// Front face
    position.PushVerticesData({Vec3{ +HALF, -HALF, +HALF  },Vec2{ THIRD + 0 * THIRD, 0.00f + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,+1}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ +HALF, +HALF, +HALF  },Vec2{ THIRD + 0 * THIRD, THIRD + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,+1}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ -HALF, +HALF, +HALF  },Vec2{ 0.00f + 0 * THIRD, THIRD + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,+1}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ +HALF, -HALF, +HALF  },Vec2{ 0.00f + 2 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{+1,+0,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});// Right face
    position.PushVerticesData({Vec3{ +HALF, -HALF, -HALF  },Vec2{ THIRD + 2 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{+1,+0,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ +HALF, +HALF, -HALF  },Vec2{ THIRD + 2 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{+1,+0,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ +HALF, +HALF, +HALF  },Vec2{ 0.00f + 2 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{+1,+0,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ +HALF, -HALF, -HALF  },Vec2{ 0.00f + 2 * THIRD, 0.00f + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,-1}.Normalize(), Texture2D::EMPTY_TEX_SLOT});// Back face
    position.PushVerticesData({Vec3{ -HALF, -HALF, -HALF  },Vec2{ THIRD + 2 * THIRD, 0.00f + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,-1}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ -HALF, +HALF, -HALF  },Vec2{ THIRD + 2 * THIRD, THIRD + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,-1}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ +HALF, +HALF, -HALF  },Vec2{ 0.00f + 2 * THIRD, THIRD + 0 * THIRD }, color.ToVec4(), Vec3{+0,+0,-1}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ -HALF, -HALF, -HALF  },Vec2{ 0.00f + 1 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{-1,+0,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});// Left face
    position.PushVerticesData({Vec3{ -HALF, -HALF, +HALF  },Vec2{ THIRD + 1 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{-1,+0,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ -HALF, +HALF, +HALF  },Vec2{ THIRD + 1 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{-1,+0,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ -HALF, +HALF, -HALF  },Vec2{ 0.00f + 1 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{-1,+0,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ -HALF, +HALF, +HALF  },Vec2{ 0.00f + 0 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{+0,+1,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});// Top face
    position.PushVerticesData({Vec3{ +HALF, +HALF, +HALF  },Vec2{ THIRD + 0 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{+0,+1,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ +HALF, +HALF, -HALF  },Vec2{ THIRD + 0 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{+0,+1,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ -HALF, +HALF, -HALF  },Vec2{ 0.00f + 0 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{+0,+1,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ -HALF, -HALF, -HALF  },Vec2{ 0.00f + 0 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{+0,-1,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});// Bottom face
    position.PushVerticesData({Vec3{ +HALF, -HALF, -HALF  },Vec2{ THIRD + 0 * THIRD, 0.00f + 1 * THIRD }, color.ToVec4(), Vec3{+0,-1,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ +HALF, -HALF, +HALF  },Vec2{ THIRD + 0 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{+0,-1,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    position.PushVerticesData({Vec3{ -HALF, -HALF, +HALF  },Vec2{ 0.00f + 0 * THIRD, THIRD + 1 * THIRD }, color.ToVec4(), Vec3{+0,-1,+0}.Normalize(), Texture2D::EMPTY_TEX_SLOT});
    // clang-format on
    return position;
  }
}

//-------------------------------------------------------------------------
Cube::Cube() : m_drawable(GetCubeVerticesPositions(), GetIndices()) {}

const Drawable& Cube::GetDrawable() const
{
  return m_drawable;
}
