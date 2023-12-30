#ifndef GRAPHICENGINE3D_GE_BUFFER_LAYOUT_HPP
#define GRAPHICENGINE3D_GE_BUFFER_LAYOUT_HPP

#include "ge_data_types.hpp"

struct BufferElem
{
  std::string name;
  ShaderDataType type;
  unsigned int size;
  unsigned int offset;
  bool normalized;
};

struct BufferLayout
{
  std::vector<BufferElem> elements;
  int stride;
};

#endif // GRAPHICENGINE3D_GE_BUFFER_LAYOUT_HPP
