#include "renderer/ge_buffer_layout.hpp"

#include <core/ge_assert.hpp>
#include <core/ge_platform.hpp>

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
    Platform::Unreachable();
  }
}

BufferLayout::BufferLayout(std::list<BufferElem> list) : m_stride(0)
{
  m_elements = { list.begin(), list.end() };
  u64 offset = 0;

  for (auto& elem : m_elements)
  {
    elem.offset = offset;
    offset += elem.size;
    m_stride += elem.size;
  }
}

std::vector<ShaderDataType> BufferLayout::GetTypesSortedList() const
{
  std::vector<ShaderDataType> sorted_list;
  sorted_list.reserve(m_elements.size());
  for (const BufferElem& e : m_elements)
    sorted_list.push_back(e.type);

  return sorted_list;
}

void BufferLayout::ForEachElement(const std::function<void(BufferElem)>& action) const
{
  for (const BufferElem& e : m_elements)
    action(e);
}

u64 BufferLayout::GetStride() const
{
  return m_stride;
}

std::list<BufferElem> GE::BufferLayout::BuildElementsList(
  std::initializer_list<std::pair<DataPurpose, ShaderDataType>> types)
{
  std::list<BufferElem> elems{};
  u64 offset = 0;
  for (const auto& [purpose, type] : types)
  {
    auto size = GetShaderDataTypeSize(type);
    elems.emplace_back(purpose, type, size, offset, false);
    offset += size;
  }
  return elems;
}
Ref<BufferLayout> GE::BufferLayout::Make(std::list<BufferElem> list)
{
  return MakeRef<BufferLayout>(std::move(list));
}

bool GE::BufferLayout::HasNormal() const
{
  return std::ranges::any_of(m_elements,
                             [&](const BufferElem& e) { return e.purpose == DataPurpose::NORMAL; });
}

BufferLayout::~BufferLayout() = default;
