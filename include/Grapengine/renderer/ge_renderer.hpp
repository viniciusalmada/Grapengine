#ifndef GRAPENGINE_RENDERER_HPP
#define GRAPENGINE_RENDERER_HPP

#include "math/ge_vector.hpp"
class VertexArray;

class Renderer
{
public:
  static void Init();

  static void SetViewport(u32 x, u32 y, u32 width, u32 height);

  static void SetClearColor(const Vec4& color);

  static void Clear();

  static void DrawIndexed(const Ref<VertexArray>& vao, i32 count);
};

#endif
