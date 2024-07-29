#ifndef GRAPENGINE_COLOR_HPP
#define GRAPENGINE_COLOR_HPP

#include "math/ge_vector.hpp"

namespace GE
{
  constexpr auto MAX_U8 = std::numeric_limits<u8>::max();
  constexpr u32 BITS_ONE_BYTE = 8;

  class Color
  {
  public:
    constexpr Color() = default;

    constexpr explicit Color(u32 argb) :
        m_alpha(static_cast<u8>((argb >> BITS_ONE_BYTE * 3) & MAX_U8)),
        m_red(static_cast<u8>((argb >> BITS_ONE_BYTE * 2) & MAX_U8)),
        m_green(static_cast<u8>((argb >> BITS_ONE_BYTE * 1) & MAX_U8)),
        m_blue(static_cast<u8>((argb >> BITS_ONE_BYTE * 0) & MAX_U8))
    {
    }

    u32 HexARGB() const;

    explicit Color(Vec3 rgb);

    template <typename T>
    [[nodiscard]] T ToVec4() const
    {
      return T{
        f32(R()) / f32(MAX_U8),
        f32(G()) / f32(MAX_U8),
        f32(B()) / f32(MAX_U8),
        f32(A()) / f32(MAX_U8),
      };
    }

    [[nodiscard]] Vec4 ToVec4() const;

    [[nodiscard]] Vec3 ToVec3() const;

    bool operator==(const Color& rhs) const = default;

    u8 A() const { return m_alpha; }
    u8 R() const { return m_red; }
    u8 G() const { return m_green; }
    u8 B() const { return m_blue; }

  private:
    u8 m_alpha = MAX_U8;
    u8 m_red = 0x00;
    u8 m_green = 0x00;
    u8 m_blue = 0x00;
  };

  namespace Colors
  {
    [[maybe_unused]] constexpr Color BLACK{ 0xFF000000 };
    [[maybe_unused]] constexpr Color WHITE{ 0xFFFFFFFF };
    [[maybe_unused]] constexpr Color RED{ 0xFFFF3333 };
    [[maybe_unused]] constexpr Color BLUE{ 0xFF3333FF };
    [[maybe_unused]] constexpr Color GREEN{ 0xFF33FF33 };
    [[maybe_unused]] constexpr Color YELLOW{ 0xFFFFFF33 };
    [[maybe_unused]] constexpr Color MAGENTA{ 0xFFFF33FF };
    [[maybe_unused]] constexpr Color ORANGE{ 0xFFF79300 }; // McLaren

    Color RandomColor();
  }
}

#endif // GRAPENGINE_COLOR_HPP
