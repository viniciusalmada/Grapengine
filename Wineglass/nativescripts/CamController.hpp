#ifndef GRAPENGINE_CAMCONTROLLER_HPP
#define GRAPENGINE_CAMCONTROLLER_HPP

#include "grapengine.hpp"

using namespace GE;

class CamController : public ScriptableEntity
{
public:
  CamController(Entity e, Scene& s) : ScriptableEntity(e, s) {}

  void OnCreate() {}
  void OnDestroy() {}
  void OnUpdate(TimeStep ts)
  {
    constexpr f32 speed = 0.01f;
    const f32 incr = speed * ts.f();

    auto& transform_comp = m_scene.GetComponent<TransformComponent>(m_entity);
    if (Input::IsKeyPressed(KeyCode::A))
      xy_cam.x -= incr;
    else if (Input::IsKeyPressed(KeyCode::D))
      xy_cam.x += incr;
    else if (Input::IsKeyPressed(KeyCode::W))
      xy_cam.y -= incr;
    else if (Input::IsKeyPressed(KeyCode::S))
      xy_cam.y += incr;

    transform_comp.transform =
      Transform::LookAt(Vec3{ 0, 0, -10 }, Vec3{ xy_cam, 0 }, Vec3{ 0, 1, 0 });
  }

private:
  Vec2 xy_cam{ 0, 0 };
};

#endif // GRAPENGINE_CAMCONTROLLER_HPP
