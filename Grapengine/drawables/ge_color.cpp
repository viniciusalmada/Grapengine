#include "ge_color.hpp"

#include "utils/ge_random.hpp"

using namespace GE;

Color Colors::RandomColor()
{
  return Color(
    Vec3{ Random::GenFloat(0.0, 1.0f), Random::GenFloat(0.0, 1.0f), Random::GenFloat(0.0, 1.0f) });
}

u32 Color::HexARGB() const
{
  u32 a = u32(A() << (BITS_ONE_BYTE * 3));
  u32 r = u32(R() << (BITS_ONE_BYTE * 2));
  u32 g = u32(G() << (BITS_ONE_BYTE * 1));
  u32 b = u32(B() << (BITS_ONE_BYTE * 0));
  return a | r | g | b;
}

Color::Color(Vec3 rgb) :
    m_alpha(0xff),
    m_red(static_cast<u8>(rgb.x * MAX_U8)),
    m_green(static_cast<u8>(rgb.y * MAX_U8)),
    m_blue(static_cast<u8>(rgb.z * MAX_U8))
{
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
