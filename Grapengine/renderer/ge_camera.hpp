#ifndef GRAPENGINE_CAMERA_HPP
#define GRAPENGINE_CAMERA_HPP

#include "math/ge_vector.hpp"

namespace GE
{
  class Camera
  {
  public:
    Camera();
    Camera(const Mat4 projection) : m_projection(projection) {}

    [[nodiscard]] const Mat4& GetProjection() const { return m_projection; }
    void SetProjection(const Mat4&);

    bool operator==(const Camera&) const = default;

  protected:
    Mat4 m_projection;
  };
}
#endif // GRAPENGINE_CAMERA_HPP
