#include "ge_scene.hpp"

#include "events/ge_event.hpp"
#include "ge_ec_registry.hpp"
#include "math/ge_vector.hpp"
#include "renderer/ge_renderer.hpp"
#include "scene/ge_components.hpp"

using namespace GE;

Scene::Scene() : m_registry({}), m_viewport(Dimension{ 1, 1 }) {}

void Scene::OnUpdate(TimeStep /*ts*/)
{
  const Entity active_camera = GetActiveCamera().value_or(Entity{});
  if (!active_camera)
    return;

  const TransformComponent& cam_transform =
    m_registry.GetComponent<TransformComponent>(active_camera);
  const CameraComponent& cam_component = m_registry.GetComponent<CameraComponent>(active_camera);

  const std::vector<Entity> g =
    m_registry.Group<TransformComponent, PrimitiveComponent, ColorOnlyComponent>();
  for (auto ent : g)
  {
    const ColorOnlyComponent shader = m_registry.GetComponent<ColorOnlyComponent>(ent);
    shader.shader->Activate();
    shader.shader->UpdateViewProjectionMatrix(cam_component.camera.GetProjection() *
                                              cam_transform.transform);

    const TransformComponent model_mat = m_registry.GetComponent<TransformComponent>(ent);
    shader.shader->UpdateModelMatrix(model_mat.transform);

    const PrimitiveComponent primitive = m_registry.GetComponent<PrimitiveComponent>(ent);
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

void Scene::OnViewportResize(Dimension dim)
{
  m_viewport = dim;

  const std::vector<Entity> camera_entities = m_registry.Group<CameraComponent>();
  for (auto ent : camera_entities)
  {
    auto& cam_comp = m_registry.GetComponent<CameraComponent>(ent);
    if (!cam_comp.fixed_ratio)
    {
      cam_comp.camera.SetViewport(dim);
    }
  }
}

Opt<Entity> Scene::GetActiveCamera() const
{
  std::vector<Entity> camera_group = m_registry.Group<TransformComponent, CameraComponent>();
  if (camera_group.empty())
  {
    GE_INFO("No camera")
    return std::nullopt;
  }

  if (std::ranges::none_of(camera_group,
                           [&](Entity ent)
                           { return m_registry.GetComponent<CameraComponent>(ent).active; }))
  {
    GE_INFO("No active camera")
    return std::nullopt;
  }

  if (std::ranges::count(
        camera_group |
          std::views::transform([&](Entity ent) -> bool
                                { return m_registry.GetComponent<CameraComponent>(ent).active; }),
        true) > 1)
  {
    GE_INFO("More than one active camera")
    return std::nullopt;
  }

  const Entity active_camera = *std::ranges::find_if(
    camera_group,
    [&](Entity ent) -> bool { return m_registry.GetComponent<CameraComponent>(ent).active; });

  return active_camera;
}
