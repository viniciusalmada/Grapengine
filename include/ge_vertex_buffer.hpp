#ifndef GRAPHICENGINE3D_GE_VERTEX_BUFFER_HPP
#define GRAPHICENGINE3D_GE_VERTEX_BUFFER_HPP

#include "ge_buffer_layout.hpp"

class VertexBuffer
{
public:
  VertexBuffer(float* ptr, uint32_t verticesSize, unsigned int parent);

  [[nodiscard]] const BufferLayout& GetLayout() const { return layout; };

  void Bind() const;

  void UpdateData(const void* data, uint32_t size);

private:
  unsigned int id = 0;
  unsigned int parent = 0;
  BufferLayout layout;
};

#endif // GRAPHICENGINE3D_GE_VERTEX_BUFFER_HPP
