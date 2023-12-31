#include "ge_buffer_layout.hpp"

struct BufferLayout::Impl
{
  std::vector<BufferElem> elements;
  i32 stride;
};

BufferLayout::BufferLayout(std::initializer_list<BufferElem> list) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->elements = list;
  u32 offset = 0;
  m_pimpl->stride = 0;

  for (auto& elem : m_pimpl->elements)
  {
    elem.offset = offset;
    offset += elem.size;
    m_pimpl->stride += elem.size;
  }
}

std::vector<ShaderDataType> BufferLayout::GetTypesSortedList() const
{
  std::vector<ShaderDataType> sorted_list;
  sorted_list.reserve(m_pimpl->elements.size());
  for (auto& e : m_pimpl->elements)
    sorted_list.push_back(e.type);

  return sorted_list;
}

void BufferLayout::ForEachElement(std::function<void(BufferElem)> action) const
{
  for (auto& e : m_pimpl->elements)
    action(e);
}

i32 BufferLayout::GetStride() const
{
  return m_pimpl->stride;
}

BufferLayout::~BufferLayout() = default;
