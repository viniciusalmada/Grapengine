#ifndef GRAPENGINE_VERTEX_BUFFER_HPP
#define GRAPENGINE_VERTEX_BUFFER_HPP

class VertexBuffer
{
public:
  GE3D VertexBuffer(const void* ptr, u64 verticesSize, u32 parent);
  GE3D ~VertexBuffer();

  void Bind() const;

  void UpdateData(const void* data, u64 size) const;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPENGINE_VERTEX_BUFFER_HPP
