#ifndef GRAPENGINE_BUFFER_LAYOUT_HPP
#define GRAPENGINE_BUFFER_LAYOUT_HPP

#include "ge_shader_data_types.hpp"

namespace GE
{
  struct BufferElem
  {
    DataPurpose purpose;
    u64 size;
    u64 offset;
    bool normalized;
  };

  class BufferLayout
  {
  public:
    explicit BufferLayout(std::list<BufferElem> list = {});
    ~BufferLayout();

    void ForEachElement(const std::function<void(BufferElem)>& action) const;

    [[nodiscard]] u64 GetStride() const;

    static std::list<BufferElem> BuildElementsList(std::initializer_list<DataPurpose> types);

  private:
    std::vector<BufferElem> m_elements;
    u64 m_stride;
  };
}
#endif // GRAPENGINE_BUFFER_LAYOUT_HPP
