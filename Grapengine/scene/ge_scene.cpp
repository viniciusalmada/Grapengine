#include "ge_scene.hpp"

#include "events/ge_event.hpp"
#include "ge_ec_registry.hpp"
#include "math/ge_vector.hpp"
#include "renderer/ge_renderer.hpp"
#include "scene/ge_components.hpp"

using namespace GE;

void Scene::OnUpdate(TimeStep /*ts*/)
{
  std::vector<Entity> camera_group = m_registry.Group<TransformComponent, CameraComponent>();
  if (camera_group.empty())
  {
    GE_INFO("No camera")
    return;
  }

  if (std::ranges::none_of(camera_group,
                           [&](Entity ent)
                           { return m_registry.GetComponent<CameraComponent>(ent).active; }))
  {
    GE_INFO("No active camera")
    return;
  }

  if (std::ranges::count(
        camera_group |
          std::views::transform([&](Entity ent) -> bool
                                { return m_registry.GetComponent<CameraComponent>(ent).active; }),
        true) > 1)
  {
    GE_INFO("More than one active camera")
    return;
  }

  Entity active_camera = *std::ranges::find_if(
    camera_group,
    [&](Entity ent) -> bool { return m_registry.GetComponent<CameraComponent>(ent).active; });

  const TransformComponent& cam_transform =
    m_registry.GetComponent<TransformComponent>(active_camera);
  const CameraComponent& cam_component = m_registry.GetComponent<CameraComponent>(active_camera);

  std::vector<Entity> g =
    m_registry.Group<TransformComponent, PrimitiveComponent, ColorOnlyComponent>();
  for (auto ent : g)
  {
    ColorOnlyComponent shader = m_registry.GetComponent<ColorOnlyComponent>(ent);
    shader.shader->Activate();
    shader.shader->UpdateViewProjectionMatrix(cam_component.cam.GetProjection() *
                                              cam_transform.transform);

    TransformComponent model_mat = m_registry.GetComponent<TransformComponent>(ent);
    shader.shader->UpdateModelMatrix(model_mat.transform);

    PrimitiveComponent primitive = m_registry.GetComponent<PrimitiveComponent>(ent);
    Renderer::DrawObject(primitive.drawing_obj);
  }
}

Entity Scene::CreateEntity(std::string_view name)
{
  Entity ent = m_registry.Create();
  AddComponent<TagComponent>(ent, name);
  return ent;
}

Ref<Scene> Scene::Make()
{
  return MakeRef<Scene>();
}

void Scene::OnEvent(Event& /*ev*/)
{
  //  auto cam_ent = m_registry.Group<CameraComponent>();
  //  auto cam = m_registry.GetComponent<CameraComponent>(cam_ent.front());
  //
  //  cam.cam->OnEvent(ev);
}

void Scene::OnResize(u32 /*w*/, u32 /*h*/)
{
  //  auto cam_ent = m_registry.Group<CameraComponent>();
  //  auto cam = m_registry.GetComponent<CameraComponent>(cam_ent.front());
  //
  //  cam.cam->OnResize(w, h);
}
