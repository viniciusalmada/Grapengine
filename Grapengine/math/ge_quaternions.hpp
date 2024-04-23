#ifndef GRAPENGINE_GE_QUATERNIONS_HPP
#define GRAPENGINE_GE_QUATERNIONS_HPP

#include "ge_transformations.hpp"
#include "ge_vector.hpp"

namespace GE
{
  class Quaternion
  {
  public:
    Quaternion(f32 angle, Vec3 axis);

    // NOLINTBEGIN(bugprone-easily-swappable-parameters)
    constexpr Quaternion(f32 w, f32 x, f32 y, f32 z) : m_w(w), m_x(x), m_y(y), m_z(z) {}
    // NOLINTEND(bugprone-easily-swappable-parameters)

    Quaternion(const Quaternion& other);

    Quaternion& operator=(const Quaternion& other);

    static constexpr Quaternion IDENTITY() { return Quaternion{ 1, 0, 0, 0 }; }

    [[nodiscard]] Quaternion Conjugate() const;

    // Quaternion multiplication
    [[nodiscard]] Quaternion operator*(const Quaternion& other) const;

    [[nodiscard]] f32 Length() const noexcept;

    [[nodiscard]] Vec3 RotateVector(Vec3 A) const;

    [[nodiscard]] Vec3 GetVec() const noexcept;

  private:
    f32 m_w = 0;
    f32 m_x = 0;
    f32 m_y = 0;
    f32 m_z = 0;
  };
}

#endif // GRAPENGINE_GE_QUATERNIONS_HPP
