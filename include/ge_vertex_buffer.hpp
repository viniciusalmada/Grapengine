#ifndef GRAPHICENGINE3D_GE_VERTEX_BUFFER_HPP
#define GRAPHICENGINE3D_GE_VERTEX_BUFFER_HPP

#include "ge_buffer_layout.hpp"

class VertexBuffer
{
public:
  VertexBuffer(float* ptr, u64 verticesSize, u32 parent);
  ~VertexBuffer();

  [[nodiscard]] const BufferLayout& GetLayout() const;;

  void Bind() const;

  void UpdateData(const void* data, u32 size);

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHICENGINE3D_GE_VERTEX_BUFFER_HPP
