#ifndef GRAPHICENGINE3D_GE_DRAW_PRIMITIVE_HPP
#define GRAPHICENGINE3D_GE_DRAW_PRIMITIVE_HPP

#include "ge_memory.hpp"
class VerticesData;

class DrawPrimitive
{
public:
  DrawPrimitive(Ref<VerticesData> vertices, const Ref<std::vector<u32>>& indices);
  ~DrawPrimitive();

  void Draw() const;

  void UpdateVerticesData(Ref<VerticesData>);

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHICENGINE3D_GE_DRAW_PRIMITIVE_HPP
