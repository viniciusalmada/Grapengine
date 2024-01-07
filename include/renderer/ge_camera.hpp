#ifndef GRAPHICENGINE3D_GE_CAMERA_HPP
#define GRAPHICENGINE3D_GE_CAMERA_HPP

#include "math/ge_vector.hpp"

class Camera
{
public:
  Camera(const Vec3& eye, float pitch, float yaw, float roll);
  Camera(const Vec3& eye, const Vec3& dir);
  ~Camera();
  Camera& operator=(const Camera&);

  Mat4 GetViewProjection() const;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHICENGINE3D_GE_CAMERA_HPP
