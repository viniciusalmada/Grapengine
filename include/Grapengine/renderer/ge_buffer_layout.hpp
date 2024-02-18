#ifndef GRAPENGINE_BUFFER_LAYOUT_HPP
#define GRAPENGINE_BUFFER_LAYOUT_HPP

#include "ge_shader_data_types.hpp"
namespace GE
{
  struct BufferElem
  {
    ShaderDataType type;
    u64 size;
    u64 offset;
    bool normalized;
  };

  class BufferLayout
  {
  public:
    explicit BufferLayout(std::list<BufferElem> list = {});
    ~BufferLayout();

    [[nodiscard]] std::vector<ShaderDataType> GetTypesSortedList() const;

    void ForEachElement(const std::function<void(BufferElem)>& action) const;

    [[nodiscard]] u64 GetStride() const;

    static std::list<BufferElem> BuildElementsList(std::initializer_list<ShaderDataType> types);

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}
#endif // GRAPENGINE_BUFFER_LAYOUT_HPP
