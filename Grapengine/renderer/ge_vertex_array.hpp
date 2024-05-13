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

    void SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, Ref<const BufferLayout> layout);
    void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

    [[nodiscard]] u32 GetID() const { return u32(id); }

  private:
    RendererID id;
    Ref<VertexBuffer> vertex_buffer;
    Ref<IndexBuffer> index_buffer;
  };
}

#endif // GRAPENGINE_VERTEXARRAY_HPP
