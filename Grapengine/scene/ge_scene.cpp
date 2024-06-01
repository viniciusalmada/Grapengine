#include "ge_scene.hpp"

#include "events/ge_event.hpp"
#include "math/ge_vector.hpp"
#include "profiling/ge_profiler.hpp"
#include "renderer/ge_renderer.hpp"
#include "scene/ge_components.hpp"
#include "scene/ge_scriptable_entity.hpp"

using namespace GE;

Scene::Scene() : m_registry({}), m_viewport(Dimension{ 1, 1 }) {}

void Scene::OnUpdate(TimeStep ts)
{
  GE_PROFILE;
  UpdateNativeScripts(ts);

  const Entity active_camera = GetActiveCamera().value_or(Entity{});
  if (!active_camera)
    return;

  const CameraComponent& cam_component = m_registry.GetComponent<CameraComponent>(active_camera);

  const std::vector<Entity> gcolor =
    m_registry.Group({ CompType::TRANSL_SCALE, CompType::PRIMITIVE, CompType::COLOR_ONLY });

  const std::vector<Entity> gmat =
    m_registry.Group({ CompType::TRANSL_SCALE, CompType::PRIMITIVE, CompType::MATERIAL });

  Renderer::Batch::Begin();
  for (auto ent : gcolor)
  {
    const ColorOnlyComponent& shader = m_registry.GetComponent<ColorOnlyComponent>(ent);
    shader.shader->Activate();
    shader.shader->UpdateViewProjectionMatrix(cam_component.camera.GetViewProjection());

    const TranslateScaleComponent& transl_scale_comp =
      m_registry.GetComponent<TranslateScaleComponent>(ent);
    //    shader.shader->UpdateModelMatrix(transl_scale_comp.GetModelMat());

    const PrimitiveComponent& primitive = m_registry.GetComponent<PrimitiveComponent>(ent);
    auto vertices = primitive.drawable->GetVerticesData(primitive.color);
    auto indices = primitive.drawable->GetIndicesData();

    Renderer::Batch::PushObject(shader.shader,
                                std::move(vertices),
                                indices,
                                transl_scale_comp.GetModelMat());
  }
  for (auto ent : gmat)
  {
    const MaterialComponent& shader = m_registry.GetComponent<MaterialComponent>(ent);
    shader.shader->Activate();
    shader.shader->UpdateViewProjectionMatrix(cam_component.camera.GetViewProjection());

    const TranslateScaleComponent& transl_scale_comp =
      m_registry.GetComponent<TranslateScaleComponent>(ent);

    const PrimitiveComponent& primitive = m_registry.GetComponent<PrimitiveComponent>(ent);
    auto vertices = primitive.drawable->GetVerticesData(primitive.color);
    auto indices = primitive.drawable->GetIndicesData();

    Renderer::Batch::PushObject(shader.shader,
                                std::move(vertices),
                                indices,
                                transl_scale_comp.GetModelMat());
  }
  Renderer::Batch::End();
}

void Scene::UpdateNativeScripts(TimeStep& ts)
{
  const std::vector<Entity> g = m_registry.Group({ CompType::NATIVE_SCRIPT });

  // Move to Scene::OnScenePlay
  for (auto ent : g)
  {
    const auto& nsc = m_registry.GetComponent<NativeScriptComponent>(ent);
    if (nsc.instance == nullptr)
    {
      nsc.instantiateFun(ent, *this);
      nsc.instance->OnCreate();
    }

    nsc.instance->OnUpdate(ts);
  }
}

Entity Scene::CreateEntity(const char* name)
{
  GE_PROFILE;
  Entity ent = m_registry.Create();
  GE_INFO("Creating entity \'{}\' with id={}", name, ent.handle)
  AddComponent<TagComponent>(ent, name);
  return ent;
}

Ptr<Scene> Scene::Make()
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

  const std::vector<Entity> camera_entities = m_registry.Group({ CompType::CAMERA });
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
  GE_PROFILE;
  std::vector<Entity> camera_group = m_registry.Group({ CompType::CAMERA });
  if (camera_group.empty())
  {
    GE_INFO("No camera")
    return std::nullopt;
  }

  if (std::ranges::none_of(camera_group,
                           [&](Entity ent)
                           {
                             const auto& cc = m_registry.GetComponent<CameraComponent>(ent);
                             return cc.active;
                           }))
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

void Scene::EachEntity(const std::function<void(Entity)>& fun) const
{
  GE_PROFILE;
  m_registry.Each(fun);
}

void Scene::UpdateActiveCamera(Entity activeCamera)
{
  GE_PROFILE;
  auto cameras = m_registry.Group({ CompType::CAMERA });
  for (const Entity& ent : cameras)
  {
    if (ent == activeCamera)
      continue;
    m_registry.GetComponent<CameraComponent>(ent).active = false;
  }
}

void Scene::DestroyEntity(Entity ent)
{
  GE_PROFILE;
  m_registry.Destroy(ent);
}
