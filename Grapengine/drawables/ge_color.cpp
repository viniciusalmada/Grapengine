#include "ge_color.hpp"

#include "utils/ge_random.hpp"

using namespace GE;

Color Colors::RandomColor()
{
  return Color(
    Vec3{ Random::GenFloat(0.0, 1.0f), Random::GenFloat(0.0, 1.0f), Random::GenFloat(0.0, 1.0f) });
}

u32 Color::HexRGB() const
{
  return m_rgb;
}

Color::Color(Vec3 rgbDec) : m_alpha(0xff), m_rgb(0xff)
{
  auto red = u8(rgbDec.x * MAX_U8);
  auto green = u8(rgbDec.y * MAX_U8);
  auto blue = u8(rgbDec.z * MAX_U8);
  m_rgb = u32(                     //
    red << (BITS_ONE_BYTE * 2) |   //
    green << (BITS_ONE_BYTE * 1) | //
    blue << (BITS_ONE_BYTE * 0)    //
  );
}

Color::Color(Vec4 rgba) : Color(Vec3{ rgba.x0, rgba.x1, rgba.x2 })
{
  m_alpha = static_cast<u8>(rgba.x3 * MAX_U8);
}

Vec4 Color::ToVec4() const
{
  return ToVec4<Vec4>();
}

Vec3 Color::ToVec3() const
{
  return {
    f32(R()) / f32(MAX_U8),
    f32(G()) / f32(MAX_U8),
    f32(B()) / f32(MAX_U8),
  };
}
