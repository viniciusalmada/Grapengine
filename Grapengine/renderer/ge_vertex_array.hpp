#ifndef GRAPENGINE_VERTEXARRAY_HPP
#define GRAPENGINE_VERTEXARRAY_HPP

#include "ge_renderer_id.hpp"
#include "ge_vertex_buffer.hpp"
#include "renderer/ge_buffer_layout.hpp"
#include "renderer/ge_index_buffer.hpp"

namespace GE
{
  class VertexArray
  {
  public:
    static Ptr<VertexArray> Make();

    VertexArray();
    ~VertexArray();

    [[nodiscard]] bool IsValid() const;
    void Bind() const;
    void Unbind() const;

    void SetVertexBuffer(const Ptr<VertexBuffer>& vertexBuffer, BufferLayout layout);
    void SetIndexBuffer(const Ptr<IndexBuffer>& indexBuffer);

    [[nodiscard]] u32 GetID() const { return u32(id); }

  private:
    RendererID id;
    Ptr<VertexBuffer> vertex_buffer;
    Ptr<IndexBuffer> index_buffer;
  };
}

#endif // GRAPENGINE_VERTEXARRAY_HPP
