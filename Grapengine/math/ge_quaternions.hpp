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
    Quaternion(f32 w, f32 x, f32 y, f32 z);
    Quaternion(const Quaternion& other);
    ~Quaternion();

    Quaternion& operator=(const Quaternion& other);

    static Quaternion IDENTITY;

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
