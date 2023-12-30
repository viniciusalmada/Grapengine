#ifndef GRAPHICENGINE3D_GE_VERTEXARRAY_HPP
#define GRAPHICENGINE3D_GE_VERTEXARRAY_HPP

#include <memory>

class VertexBuffer;
class IndexBuffer;

class VertexArray
{
public:
  VertexArray();
  ~VertexArray();

  void Bind() const;

  void SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
  void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

  [[nodiscard]] u32 GetID() const { return id; }

private:
  u32 id;
  Ref<VertexBuffer> vertex_buffer;
  Ref<IndexBuffer> index_buffer;
};

#endif // GRAPHICENGINE3D_GE_VERTEXARRAY_HPP
