#ifndef GRAPENGINE_CAMCONTROLLER_HPP
#define GRAPENGINE_CAMCONTROLLER_HPP

#include "grapengine.hpp"

using namespace GE;

class CamController final : public ScriptableEntity
{
public:
  CamController(Entity e, Scene& s) : ScriptableEntity(e, s), xy_cam({}) {}

  void OnCreate() override
  {
    const f32 x = GE::Random::GenFloat(0, 5);
    const f32 y = GE::Random::GenFloat(0, 5);
    xy_cam = Vec2{ x, y };
  }
  void OnDestroy() override {}
  void OnUpdate(TimeStep ts) override
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
  Vec2 xy_cam;
};

#endif // GRAPENGINE_CAMCONTROLLER_HPP
