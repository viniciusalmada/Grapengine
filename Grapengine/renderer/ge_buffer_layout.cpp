#include "renderer/ge_buffer_layout.hpp"

#include "core/ge_platform.hpp"

using namespace GE;

namespace
{
  u64 GetShaderDataTypeSize(DataPurpose t)
  {
    switch (t)
    {
    case DataPurpose::POSITION_F3:
    case DataPurpose::NORMAL_F3:
      return sizeof(f32) * 3;
    case DataPurpose::COLOR_F4:
      return sizeof(f32) * 4;
    case DataPurpose::TEXTURE_COORDINATE_F2:
      return sizeof(f32) * 2;
    case DataPurpose::TEX_ID_INT:
      return sizeof(i32);
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

void BufferLayout::ForEachElement(const std::function<void(BufferElem)>& action) const
{
  std::ranges::for_each(m_elements, action);
}

u64 BufferLayout::GetStride() const
{
  return m_stride;
}

std::list<BufferElem> GE::BufferLayout::BuildElementsList(std::initializer_list<DataPurpose> types)
{
  std::list<BufferElem> elems{};
  u64 offset = 0;
  for (const auto& purpose : types)
  {
    auto size = GetShaderDataTypeSize(purpose);
    elems.emplace_back(purpose, size, offset, false);
    offset += size;
  }
  return elems;
}

BufferLayout::~BufferLayout() = default;
