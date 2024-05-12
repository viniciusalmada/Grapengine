#ifndef GRAPENGINE_GE_SCENE_CAMERA_HPP
#define GRAPENGINE_GE_SCENE_CAMERA_HPP

#include "renderer/ge_camera.hpp"

#include <utils/ge_dimension.hpp>

namespace GE
{

  class SceneCamera final : public Camera
  {
  public:
    SceneCamera();
    SceneCamera(const SceneCamera&);
    ~SceneCamera() override = default;

    [[nodiscard]] Mat4 GetViewProjection() const;
    [[nodiscard]] Vec3 GetPosition() const { return m_position; }
    [[nodiscard]] Vec3 GetTarget() const { return m_target; }

    void SetView(Vec3 position, Vec3 target);
    void SetViewport(Dimension vp);

  private:
    void RecalculateProjection();

    Vec3 m_position;
    Vec3 m_target;
    Dimension m_viewport;
  };

} // GE

#endif // GRAPENGINE_GE_SCENE_CAMERA_HPP
