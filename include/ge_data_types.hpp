#ifndef GRAPHIC_ENGINE3D_GE_DATA_TYPES_HPP
#define GRAPHIC_ENGINE3D_GE_DATA_TYPES_HPP

#include "ge_vector.hpp"

struct SimpleVertexData
{
  Vec3 position;
  Vec4 color;
};

enum class ShaderDataType
{
  None,
  Float,
  Float2,
  Float3,
  Float4,
  Mat3,
  Mat4,
  Int,
  Int2,
  Int3,
  Int4,
  Bool
};


#endif
