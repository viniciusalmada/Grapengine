#ifndef GRAPHICENGINE3D_GE_COLOR_HPP
#define GRAPHICENGINE3D_GE_COLOR_HPP

#include "math/ge_vector.hpp"

struct Color
{
  u8 R = 0x00;
  u8 G = 0x00;
  u8 B = 0x00;
  u8 A = 0xFF;

  Vec4 ToVec4()
  {
    return {
      R / 255.0f,
      G / 255.0f,
      B / 255.0f,
      A / 255.0f,
    };
  }
};

namespace Colors
{
  constexpr Color BLACK{};
  constexpr Color WHITE{ 0xFF, 0xFF, 0xFF, 0xFF };
  constexpr Color RED{ 0xFF, 0x00, 0x00, 0xFF };
}

#endif // GRAPHICENGINE3D_GE_COLOR_HPP
