#ifndef GRAPHICENGINE3D_GE_BUFFER_LAYOUT_HPP
#define GRAPHICENGINE3D_GE_BUFFER_LAYOUT_HPP

#include "ge_data_types.hpp"

struct BufferElem
{
  std::string name;
  ShaderDataType type;
  u32 size;
  u32 offset;
  bool normalized;
};

class BufferLayout
{
public:
  BufferLayout(std::initializer_list<BufferElem> list = {});
  ~BufferLayout();

  [[nodiscard]] std::vector<ShaderDataType> GetTypesSortedList() const;

  void ForEachElement(const std::function<void(BufferElem)>& action) const;

  [[nodiscard]] u32 GetStride() const;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHICENGINE3D_GE_BUFFER_LAYOUT_HPP
