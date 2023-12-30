#ifndef GRAPHICENGINE3D_GE_VERTEX_BUFFER_HPP
#define GRAPHICENGINE3D_GE_VERTEX_BUFFER_HPP

#include "ge_buffer_layout.hpp"

class VertexBuffer
{
public:
  VertexBuffer(float* ptr, u32 verticesSize, u32 parent);

  [[nodiscard]] const BufferLayout& GetLayout() const { return layout; };

  void Bind() const;

  void UpdateData(const void* data, u32 size);

private:
  u32 id = 0;
  u32 parent = 0;
  BufferLayout layout;
};

#endif // GRAPHICENGINE3D_GE_VERTEX_BUFFER_HPP
