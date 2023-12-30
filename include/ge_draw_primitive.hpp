#ifndef GRAPHICENGINE3D_GE_DRAW_PRIMITIVE_HPP
#define GRAPHICENGINE3D_GE_DRAW_PRIMITIVE_HPP

#include "ge_memory.hpp"
struct SimpleVertexData;

class DrawPrimitive
{
public:
  DrawPrimitive(const Ref<std::vector<SimpleVertexData>>& vertices, const Ref<std::vector<u32>>& indices);
  ~DrawPrimitive();

  void Draw() const;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHICENGINE3D_GE_DRAW_PRIMITIVE_HPP
