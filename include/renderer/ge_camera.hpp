#ifndef GRAPHICENGINE3D_GE_CAMERA_HPP
#define GRAPHICENGINE3D_GE_CAMERA_HPP

#include "math/ge_vector.hpp"

class Camera
{
public:
  GE3D Camera(const Vec3& eye, float pitch, float yaw, float roll);
  GE3D Camera(const Vec3& eye, const Vec3& dir);
  GE3D ~Camera();
  Camera& operator=(const Camera&);

  GE3D Mat4 GetViewProjection(u32 width, u32 height) const;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHICENGINE3D_GE_CAMERA_HPP
