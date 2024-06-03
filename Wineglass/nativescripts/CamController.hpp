#ifndef GRAPENGINE_CAMCONTROLLER_HPP
#define GRAPENGINE_CAMCONTROLLER_HPP

#include "grapengine.hpp"

using namespace GE;

class CamController final : public ScriptableEntity
{
public:
  CamController(Entity e, Scene& s) : ScriptableEntity(e, s), xyz_cam({ 0, 0, 10 }) {}
  ~CamController() override;

  void OnCreate() override
  {
  }
  void OnDestroy() override {}
  void OnUpdate(TimeStep ts) override
  {
    constexpr f32 speed = 0.01f;
    const f32 incr = speed * ts.f();

    auto& camera_comp = m_scene.GetComponent<CameraComponent>(m_entity);
    if (!camera_comp.active)
      return;

    if (Input::IsKeyPressed(KeyCode::A))
      xyz_cam.x += incr;
    else if (Input::IsKeyPressed(KeyCode::D))
      xyz_cam.x -= incr;
    else if (Input::IsKeyPressed(KeyCode::W))
      xyz_cam.y -= incr;
    else if (Input::IsKeyPressed(KeyCode::S))
      xyz_cam.y += incr;
    else if (Input::IsKeyPressed(KeyCode::E))
      xyz_cam.z -= incr;
    else if (Input::IsKeyPressed(KeyCode::Q))
      xyz_cam.z += incr;

    auto camera_pos = camera_comp.camera.GetPosition();
    auto camera_tar = camera_comp.camera.GetTarget();
    camera_pos.x = xyz_cam.x;
    camera_pos.y = xyz_cam.y;
    camera_pos.z = xyz_cam.z;
    camera_tar.x = xyz_cam.x;
    camera_tar.y = xyz_cam.y;
    camera_comp.camera.SetView(camera_pos, camera_tar);
  }

private:
  Vec3 xyz_cam;
};

#endif // GRAPENGINE_CAMCONTROLLER_HPP
