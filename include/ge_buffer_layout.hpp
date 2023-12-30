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

struct BufferLayout
{
  std::vector<BufferElem> elements;
  i32 stride;
};

#endif // GRAPHICENGINE3D_GE_BUFFER_LAYOUT_HPP
