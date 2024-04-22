#ifndef GRAPENGINE_CAMERA_HPP
#define GRAPENGINE_CAMERA_HPP

#include "math/ge_vector.hpp"

namespace GE
{
  class Camera
  {
  public:
    Camera(const Mat4 projection) : m_projection(projection) {}

    [[nodiscard]] const Mat4& GetProjection() const { return m_projection; }

  private:
    Mat4 m_projection;
  };
}
#endif // GRAPENGINE_CAMERA_HPP
