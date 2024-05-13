#ifndef GRAPENGINE_CAMCONTROLLER_HPP
#define GRAPENGINE_CAMCONTROLLER_HPP

#include "grapengine.hpp"

using namespace GE;

class CamController final : public ScriptableEntity
{
public:
  CamController(Entity e, Scene& s) : ScriptableEntity(e, s), xy_cam({}) {}
  ~CamController() override;

  void OnCreate() override
  {
    //    const f32 x = GE::Random::GenFloat(0, 5);
    //    const f32 y = GE::Random::GenFloat(0, 5);
    //    xy_cam = Vec2{ x, y };
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
      xy_cam.x -= incr;
    else if (Input::IsKeyPressed(KeyCode::D))
      xy_cam.x += incr;
    else if (Input::IsKeyPressed(KeyCode::W))
      xy_cam.y -= incr;
    else if (Input::IsKeyPressed(KeyCode::S))
      xy_cam.y += incr;

    auto camera_pos = camera_comp.camera.GetPosition();
    auto camera_tar = camera_comp.camera.GetTarget();
    camera_pos.x = xy_cam.x;
    camera_pos.y = xy_cam.y;
    camera_tar.x = xy_cam.x;
    camera_tar.y = xy_cam.y;
    camera_comp.camera.SetView(camera_pos, camera_tar);
  }

private:
  Vec2 xy_cam;
};

CamController::~CamController() = default;

#endif // GRAPENGINE_CAMCONTROLLER_HPP
