#ifndef GRAPHICENGINE3D_GE_VERTEX_BUFFER_HPP
#define GRAPHICENGINE3D_GE_VERTEX_BUFFER_HPP

class VertexBuffer
{
public:
  GE3D VertexBuffer(const void* ptr, u64 verticesSize, u32 parent);
  GE3D ~VertexBuffer();

  void Bind() const;

  void UpdateData(const void* data, u64 size);

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHICENGINE3D_GE_VERTEX_BUFFER_HPP
