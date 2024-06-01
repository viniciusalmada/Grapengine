#ifndef GRAPENGINE_INDEX_BUFFER_HPP
#define GRAPENGINE_INDEX_BUFFER_HPP

#include "ge_renderer_id.hpp"

namespace GE
{
  class IndexBuffer
  {
  public:
    static Ptr<IndexBuffer> Make(const std::vector<u32>& indices, RendererID parent);

    IndexBuffer(const std::vector<u32>& indices, u32 count, RendererID parent);

    void Bind() const;

    void UpdateData(const std::vector<u32>& indices);

  private:
    RendererID m_id;
    RendererID m_parent;
  };
}
#endif // GRAPENGINE_INDEX_BUFFER_HPP
