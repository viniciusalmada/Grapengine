#ifndef GRAPENGINE_COLOR_HPP
#define GRAPENGINE_COLOR_HPP

#include "math/ge_vector.hpp"

namespace GE
{
  constexpr auto MAX_U8 = std::numeric_limits<u8>::max();
  constexpr auto BITS_ONE_BYTE = 8;

  struct Color
  {
    u8 R = 0x00;
    u8 G = 0x00;
    u8 B = 0x00;
    u8 A = MAX_U8;

    constexpr explicit Color(u32 rgba) :
        R(static_cast<u8>((rgba >> BITS_ONE_BYTE * 3) & MAX_U8)),
        G(static_cast<u8>((rgba >> BITS_ONE_BYTE * 2) & MAX_U8)),
        B(static_cast<u8>((rgba >> BITS_ONE_BYTE * 1) & MAX_U8)),
        A(static_cast<u8>((rgba >> BITS_ONE_BYTE * 0) & MAX_U8))
    {
    }

    explicit Color(Vec3 rgb) :
        R(static_cast<u8>(rgb.x * MAX_U8)),
        G(static_cast<u8>(rgb.y * MAX_U8)),
        B(static_cast<u8>(rgb.z * MAX_U8))
    {
    }

    explicit Color(Vec4 rgb) :
        R(static_cast<u8>(rgb.x0 * MAX_U8)),
        G(static_cast<u8>(rgb.x1 * MAX_U8)),
        B(static_cast<u8>(rgb.x2 * MAX_U8)),
        A(static_cast<u8>(rgb.x3 * MAX_U8))
    {
    }

    template <typename T>
    [[nodiscard]] T ToVec4() const
    {
      return T{
        f32(R) / f32(MAX_U8),
        f32(G) / f32(MAX_U8),
        f32(B) / f32(MAX_U8),
        f32(A) / f32(MAX_U8),
      };
    }

    [[nodiscard]] Vec4 ToVec4() const { return ToVec4<Vec4>(); }

    [[nodiscard]] Vec3 ToVec3() const
    {
      return {
        f32(R) / f32(MAX_U8),
        f32(G) / f32(MAX_U8),
        f32(B) / f32(MAX_U8),
      };
    }

    bool operator==(const Color& rhs) const;
    bool operator!=(const Color& rhs) const;
  };

  namespace Colors
  {
    [[maybe_unused]] constexpr Color BLACK{ 0x000000FF };
    [[maybe_unused]] constexpr Color WHITE{ 0xFFFFFFFF };
    [[maybe_unused]] constexpr Color RED{ 0xFF3333FF };
    [[maybe_unused]] constexpr Color BLUE{ 0x3333FFFF };
    [[maybe_unused]] constexpr Color GREEN{ 0x33FF33FF };
    [[maybe_unused]] constexpr Color YELLOW{ 0xFFFF33FF };
    [[maybe_unused]] constexpr Color MAGENTA{ 0xFF33FFFF };
    [[maybe_unused]] constexpr Color ORANGE{ 0xF79300 }; // McLaren

    Color RandomColor();
  }
}

#endif // GRAPENGINE_COLOR_HPP
