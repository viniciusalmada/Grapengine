#ifndef GRAPENGINE_VERTEX_BUFFER_HPP
#define GRAPENGINE_VERTEX_BUFFER_HPP
#include "ge_renderer_id.hpp"
namespace GE
{
  class VertexBuffer
  {
  public:
    static Ptr<VertexBuffer> Make(const void* ptr, u64 verticesSize, RendererID parent);

    VertexBuffer(const void* ptr, u64 verticesSize, RendererID parent);

    void Bind() const;

    void UpdateData(const void* data, u64 size) const;

  private:
    RendererID m_id = 0;
    RendererID m_parent = 0;
  };
}

#endif // GRAPENGINE_VERTEX_BUFFER_HPP
