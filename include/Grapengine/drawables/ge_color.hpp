#ifndef GRAPENGINE_COLOR_HPP
#define GRAPENGINE_COLOR_HPP

#include "math/ge_vector.hpp"

namespace GE
{
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
    constexpr Color RED{ 0xFF, 0x33, 0x33, 0xFF };
    constexpr Color BLUE{ 0x33, 0x33, 0xFF, 0xFF };
    constexpr Color GREEN{ 0x33, 0xFF, 0x33, 0xFF };
    constexpr Color MAGENTA{ 0xFF, 0x33, 0xFF, 0xFF };
  }
}

#endif // GRAPENGINE_COLOR_HPP
