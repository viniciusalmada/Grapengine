#ifndef GRAPHIC_ENGINE3D_GE_RENDERER_HPP
#define GRAPHIC_ENGINE3D_GE_RENDERER_HPP

#include "ge_vector.hpp"
class VertexArray;

class Renderer
{
public:
  static void Init();

  static void SetViewport(u32 x, u32 y, u32 width, u32 height);

  static void SetClearColor(const Vec4& color);

  static void Clear();

  static void DrawIndexed(Ref<VertexArray> vao, i32 count);
};

#endif
