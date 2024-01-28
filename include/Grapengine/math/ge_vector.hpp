#ifndef GRAPENGINE_VECTOR_HPP
#define GRAPENGINE_VECTOR_HPP

#include "core/ge_config.hpp"
#include "core/ge_type_aliases.hpp"

#include <array>
namespace GE
{
  struct GE3D Vec2
  {
    float x;
    float y;
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator+(const Vec2& other) const;
  };

  struct GE3D Vec3
  {
    float x;
    float y;
    float z;

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3& operator-();
    Vec3 operator*(float fac) const;
    [[nodiscard]] Vec3 Normalize() const;
    [[nodiscard]] Vec3 Cross(const Vec3& other) const;
    [[nodiscard]] float Dot(const Vec3& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Vec3& vec3);
  };

  struct Vec4
  {
    float x0;
    float x1;
    float x2;
    float x3;
  };

  class GE3D Mat4
  {
  public:
    Mat4();

    Mat4(const std::array<float, 4>& row0,
         const std::array<float, 4>& row1,
         const std::array<float, 4>& row2,
         const std::array<float, 4>& row3);

    bool operator==(const Mat4& other) const;
    Mat4 operator*(const Mat4& other) const;

    float& operator()(u32 row, u32 col);
    const float& operator()(u32 row, u32 col) const;

    [[nodiscard]] const float* ValuePtr() const;

  private:
    std::array<std::array<float, 4>, 4> data{ { { 0.0f } } };
  };
}
#endif
