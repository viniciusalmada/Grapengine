#ifndef GRAPHIC_ENGINE3D_GE_RENDERER_HPP
#define GRAPHIC_ENGINE3D_GE_RENDERER_HPP

#include "ge_vector.hpp"
class VertexArray;

class Renderer
{
public:
  static void Init();

  static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

  static void SetClearColor(const Vec4& color);

  static void Clear();

  static void DrawIndexed(std::shared_ptr<VertexArray> vao, int count);
};

#endif
