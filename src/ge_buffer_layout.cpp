#include "renderer/ge_buffer_layout.hpp"

using namespace GE;

namespace
{
  u64 GetShaderDataTypeSize(ShaderDataType t)
  {
    switch (t)
    {
    case ShaderDataType::None:
      return 0;
    case ShaderDataType::Float:
      return sizeof(f32);
    case ShaderDataType::Float2:
      return sizeof(f32) * 2;
    case ShaderDataType::Float3:
      return sizeof(f32) * 3;
    case ShaderDataType::Float4:
      return sizeof(f32) * 4;
    case ShaderDataType::Mat3:
      return sizeof(f32) * 3 * 3;
    case ShaderDataType::Mat4:
      return sizeof(f32) * 4 * 4;
    case ShaderDataType::Int:
      return sizeof(int);
    case ShaderDataType::Int2:
      return sizeof(int) * 2;
    case ShaderDataType::Int3:
      return sizeof(int) * 3;
    case ShaderDataType::Int4:
      return sizeof(int) * 4;
    case ShaderDataType::Bool:
      return 1;
    }
    __builtin_unreachable();
  }
}

struct BufferLayout::Impl
{
  std::vector<BufferElem> elements;
  u64 stride = 0;
};

BufferLayout::BufferLayout(std::list<BufferElem> list) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->elements = { list.begin(), list.end() };
  u64 offset = 0;
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

void BufferLayout::ForEachElement(const std::function<void(BufferElem)>& action) const
{
  for (auto& e : m_pimpl->elements)
    action(e);
}

u64 BufferLayout::GetStride() const
{
  return m_pimpl->stride;
}

std::list<BufferElem>
GE::BufferLayout::BuildElementsList(std::initializer_list<ShaderDataType> types)
{
  std::list<BufferElem> elems{};
  u64 offset = 0;
  for (ShaderDataType type : types)
  {
    auto size = GetShaderDataTypeSize(type);
    elems.emplace_back(type, size, offset, false);
    offset += size;
  }
  return elems;
}

BufferLayout::~BufferLayout() = default;
