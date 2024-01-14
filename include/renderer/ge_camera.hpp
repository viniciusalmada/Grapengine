#ifndef GRAPHICENGINE3D_GE_CAMERA_HPP
#define GRAPHICENGINE3D_GE_CAMERA_HPP

#include "math/ge_vector.hpp"

class Camera
{
public:
  GE3D Camera(float aspectRatio, const Vec3& eye, float pitch, float yaw);
  GE3D Camera(float aspectRatio, const Vec3& eye, const Vec3& dir);
  GE3D ~Camera();
  Camera& operator=(const Camera&);

  [[nodiscard]] bool IsMoving() const;
  void StartMovement(Vec2 referencePoint) const;
  void StopMovement() const;
  void MeasureMovement(Vec2 currentPoint) const;

  GE3D Mat4 GetViewProjection() const;
  void SetAspectRatio(float ratio) const;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHICENGINE3D_GE_CAMERA_HPP
