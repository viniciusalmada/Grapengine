#ifndef GRAPHICENGINE3D_GE_RENDERER_HPP
#define GRAPHICENGINE3D_GE_RENDERER_HPP

#include "ge_vector.hpp"

class Renderer
{
public:
  static void Init();

  static void SetViewpport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

  static void SetClearColor(const Vec4& color);

  static void Clear();


};

#endif // GRAPHICENGINE3D_GE_RENDERER_HPP
