#ifndef GRAPENGINE_CAMERA_HPP
#define GRAPENGINE_CAMERA_HPP

#include "core/ge_macros.hpp"
#include "math/ge_vector.hpp"
namespace GE
{
  class Camera
  {
  public:
    GE3D Camera(float aspectRatio, const Vec3& eye, float pitch, float yaw);
    GE3D Camera(float aspectRatio, const Vec3& eye, const Vec3& dir);
    GE3D ~Camera();

    [[nodiscard]] bool IsAiming() const;
    void StartAiming(Vec2 referencePoint) const;
    void StopAiming() const;
    void ChangeAimPoint(Vec2 currentPoint) const;

    [[nodiscard]] bool IsMoving() const;
    void StartMoving(Vec2 referencePoint) const;
    void StopMoving() const;
    void ChangeLocation(Vec2 currentPoint) const;

    bool IsRotating() const;
    void StartRotating(Vec2 referencePoint) const;
    void StopRotating() const;
    void ChangeAngle(Vec2 currentPoint) const;

    void SetZoom(float diffY) const;

    GE3D Mat4 GetViewProjection() const;
    void SetAspectRatio(float ratio) const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}
#endif // GRAPENGINE_CAMERA_HPP
