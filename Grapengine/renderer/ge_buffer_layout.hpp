#ifndef GRAPENGINE_BUFFER_LAYOUT_HPP
#define GRAPENGINE_BUFFER_LAYOUT_HPP

#include "ge_shader_data_types.hpp"
namespace GE
{
  struct BufferElem
  {
    DataPurpose purpose;
    ShaderDataType type;
    u64 size;
    u64 offset;
    bool normalized;
  };

  class BufferLayout
  {
  public:
    static Ref<BufferLayout> Make(std::list<BufferElem> list);

    explicit BufferLayout(std::list<BufferElem> list = {});
    ~BufferLayout();

    [[nodiscard]] std::vector<ShaderDataType> GetTypesSortedList() const;

    void ForEachElement(const std::function<void(BufferElem)>& action) const;

    [[nodiscard]] u64 GetStride() const;

    [[nodiscard]] bool HasNormal() const;

    static std::list<BufferElem>
    BuildElementsList(std::initializer_list<std::pair<DataPurpose, ShaderDataType>> types);

  private:
    std::vector<BufferElem> m_elements;
    u64 m_stride = 0;
  };
}
#endif // GRAPENGINE_BUFFER_LAYOUT_HPP
