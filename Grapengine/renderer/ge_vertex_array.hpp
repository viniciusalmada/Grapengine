#ifndef GRAPENGINE_VERTEXARRAY_HPP
#define GRAPENGINE_VERTEXARRAY_HPP

#include "ge_renderer_id.hpp"

namespace GE
{
  class VertexBuffer;
  class IndexBuffer;
  class BufferLayout;

  class VertexArray
  {
  public:
    VertexArray();
    ~VertexArray();

    [[nodiscard]] bool IsValid() const;
    void Bind() const;
    void Unbind() const;

    void SetVertexBuffer(const Ptr<VertexBuffer>& vertexBuffer, Ptr<const BufferLayout> layout);
    void SetIndexBuffer(const Ptr<IndexBuffer>& indexBuffer);

    [[nodiscard]] u32 GetID() const { return u32(id); }

  private:
    RendererID id;
    Ptr<VertexBuffer> vertex_buffer;
    Ptr<IndexBuffer> index_buffer;
  };
}

#endif // GRAPENGINE_VERTEXARRAY_HPP
