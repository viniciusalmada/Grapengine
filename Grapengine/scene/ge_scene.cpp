#include "ge_scene.hpp"

#include "events/ge_event.hpp"
#include "ge_ec_registry.hpp"
#include "math/ge_vector.hpp"
#include "renderer/ge_renderer.hpp"
#include "scene/ge_components.hpp"

using namespace GE;

Scene::Scene() {}

void GE::Scene::OnUpdate(TimeStep ts)
{
  auto cam_ent = m_registry.Group<EditorCameraComponent>();
  auto cam = m_registry.GetComponent<EditorCameraComponent>(cam_ent.front());

  cam.cam->OnUpdate(ts);

  auto g = m_registry.Group<TransformComponent, PrimitiveComponent, ColorOnlyComponent>();
  for (auto ent : g)
  {
    ColorOnlyComponent shader = m_registry.GetComponent<ColorOnlyComponent>(ent);
    shader.shader->Activate();
    shader.shader->UpdateViewProjectionMatrix(cam.cam->GetViewProjection());

    TransformComponent model_mat = m_registry.GetComponent<TransformComponent>(ent);
    shader.shader->UpdateModelMatrix(model_mat.model);

    PrimitiveComponent primitive = m_registry.GetComponent<PrimitiveComponent>(ent);
    Renderer::DrawObject(primitive.drawing_obj);
  }
}

Entity GE::Scene::CreateEntity(std::string_view name)
{
  Entity ent = m_registry.Create();
  AddComponent<TagComponent>(ent, name);
  return ent;
}
Ref<Scene> GE::Scene::Make()
{
  return MakeRef<Scene>();
}

void Scene::OnEvent(Event& ev)
{
  auto cam_ent = m_registry.Group<EditorCameraComponent>();
  auto cam = m_registry.GetComponent<EditorCameraComponent>(cam_ent.front());

  cam.cam->OnEvent(ev);
}

void Scene::OnResize(u32 w, u32 h)
{
  auto cam_ent = m_registry.Group<EditorCameraComponent>();
  auto cam = m_registry.GetComponent<EditorCameraComponent>(cam_ent.front());

  cam.cam->OnResize(w, h);
}

Scene::~Scene() = default;
