#ifndef GRAPENGINE_VECTOR_HPP
#define GRAPENGINE_VECTOR_HPP

#include "core/ge_config.hpp"
#include "core/ge_type_aliases.hpp"

#include <array>
#include <format>
#include <ostream>

namespace GE
{
  struct IVec2
  {
    i32 x;
    i32 y;
  };

  struct Vec2
  {
    f32 x;
    f32 y;
    Vec2 operator-(const Vec2& other) const noexcept;
    Vec2 operator+(const Vec2& other) const noexcept;
    Vec2 operator*(f32 fac) const;
    [[nodiscard]] f32 Length() const noexcept;
    [[nodiscard]] f32 Dot(Vec2 other) const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec)
    {
      os << std::format("{:1.2f},{:1.2f}", vec.x, vec.y);
      return os;
    }
    bool operator==(const Vec2& rhs) const;
    bool operator!=(const Vec2& rhs) const;
  };

  struct IVec3
  {
    i32 x;
    i32 y;
    i32 z;

    bool operator<(const IVec3& other) const;
  };

  struct Vec3
  {
    f32 x;
    f32 y;
    f32 z;

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3& operator-();
    Vec3 operator*(f32 fac) const;
    Vec3& operator+=(const Vec3& other);
    [[nodiscard]] Vec3 Normalize() const;
    [[nodiscard]] Vec3 Cross(const Vec3& other) const;
    [[nodiscard]] f32 Dot(const Vec3& other) const;
    [[nodiscard]] f32 Distance(const Vec3& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Vec3& vec3)
    {
      os << std::format("{:1.2f},{:1.2f},{:1.2f}", vec3.x, vec3.y, vec3.z);
      return os;
    }
    [[nodiscard]] f32 Length() const;
  };

  struct Vec4
  {
    f32 x0;
    f32 x1;
    f32 x2;
    f32 x3;
  };

  class Mat4
  {
  public:
    Mat4();

    Mat4(const std::array<f32, 4>& row0,
         const std::array<f32, 4>& row1,
         const std::array<f32, 4>& row2,
         const std::array<f32, 4>& row3);

    bool operator==(const Mat4& other) const;
    Mat4 operator*(const Mat4& other) const;

    f32& operator()(u32 row, u32 col);
    const f32& operator()(u32 row, u32 col) const;

    [[nodiscard]] const f32* ValuePtr() const;

  private:
    std::array<std::array<f32, 4>, 4> data{ { { 0.0F } } };
  };
}
#endif
