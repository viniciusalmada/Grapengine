#ifndef GRAPENGINE_DATA_TYPES_HPP
#define GRAPENGINE_DATA_TYPES_HPP

#include "math/ge_vector.hpp"
namespace GE
{
  enum class ShaderDataType : u8
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

  enum class DataPurpose : u8
  {
    POSITION_F3,
    COLOR_F4,
    TEXTURE_COORDINATE_F2,
    NORMAL_F3
  };
}

#endif
