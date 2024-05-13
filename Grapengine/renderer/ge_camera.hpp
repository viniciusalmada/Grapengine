#ifndef GRAPENGINE_CAMERA_HPP
#define GRAPENGINE_CAMERA_HPP

#include "math/ge_vector.hpp"

namespace GE
{
  class Camera
  {
  public:
    Camera();
    Camera(const Camera&) = delete;
    Camera(const Mat4 projection) : m_projection(projection) {}
    virtual ~Camera();

    [[nodiscard]] const Mat4& GetProjection() const { return m_projection; }

  protected:
    Mat4 m_projection;
  };
}
#endif // GRAPENGINE_CAMERA_HPP
