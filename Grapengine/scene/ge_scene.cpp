#include "ge_scene.hpp"

#include "events/ge_event.hpp"
#include "math/ge_vector.hpp"
#include "profiling/ge_profiler.hpp"
#include "renderer/ge_renderer.hpp"
#include "scene/ge_components.hpp"
#include "scene/ge_scriptable_entity.hpp"
#include "utils/ge_random.hpp"

using namespace GE;

Scene::Scene() : m_registry({}), m_active_camera(std::nullopt), m_viewport(Dimension{ 1, 1 }) {}

void Scene::OnUpdate(TimeStep ts)
{
  GE_PROFILE;
  UpdateNativeScripts(ts);
  UpdateActiveCamera();
  UpdateLightSourcesPosition(ts);
  UpdateLightSources();
  UpdateAmbientLight();
  UpdateDrawableEntities(ts);
}

void Scene::UpdateLightSources() const
{
  auto light_sources = m_registry.Group<LightSourceComponent>();
  if (!light_sources.empty())
  {
    std::vector<LightSource> props;
    props.reserve(light_sources.size());

    std::ranges::transform(
      light_sources,
      std::back_inserter(props),
      [&](Entity l) -> LightSource
      {
        const auto& lp = m_registry.GetComponent<LightSourceComponent>(l);
        return { lp.GetPos(), lp.GetColor(), lp.IsActive() ? lp.GetStr() : 0.0f, 0.5f, 32.0f };
      });
    Renderer::SetLightSources(props);
  }
}

void Scene::UpdateAmbientLight() const
{
  auto amb_lights = m_registry.Group<AmbientLightComponent>();
  if (!amb_lights.empty())
  {
    auto amb_light_itr = std::ranges::find_if(
      amb_lights,
      [&](Entity al) { return m_registry.GetComponent<AmbientLightComponent>(al).IsActive(); });

    if (amb_light_itr != amb_lights.end())
    {
      const AmbientLightComponent& amb_light =
        m_registry.GetComponent<AmbientLightComponent>(*amb_light_itr);
      Renderer::SetAmbientLight(amb_light.GetColor(), amb_light.GetStr());
    }
  }
}

void Scene::UpdateActiveCamera()
{
  if (!m_active_camera)
  {
    m_active_camera = RetrieveActiveCamera();
  }
}

void Scene::UpdateNativeScripts(TimeStep& ts)
{
  GE_PROFILE;
  const std::vector<Entity> g = m_registry.Group<NativeScriptComponent>();

  // Move to Scene::OnScenePlay
  for (auto ent : g)
  {
    const auto& nsc = m_registry.GetComponent<NativeScriptComponent>(ent);
    if (!nsc.IsValid())
    {
      nsc.Instantiate(ent, *this);
      nsc.GetInstance()->OnCreate();
    }

    nsc.GetInstance()->OnUpdate(ts);
  }
}

void Scene::UpdateDrawableEntities(TimeStep& /*ts*/)
{
  GE_PROFILE;
  if (!m_active_camera.has_value())
  {
    GE_ASSERT(false, "No active camera!")
    return;
  }

  const auto& active_camera = m_active_camera.value();

  const CameraComponent& cam_component = m_registry.GetComponent<CameraComponent>(active_camera);

  const std::vector<Entity> gmat = m_registry.Group<TransformComponent, PrimitiveComponent>();

  {
    GE_PROFILE_SECTION("Batch renderer");
    Renderer::Batch::Begin(cam_component.GetCamera().GetViewProjection(),
                           cam_component.GetCamera().GetPosition());
    for (auto ent : gmat)
    {
      const TransformComponent& transl_scale_comp =
        m_registry.GetComponent<TransformComponent>(ent);

      PrimitiveComponent& primitive = m_registry.GetComponent<PrimitiveComponent>(ent);
      primitive.GetDrawable().UpdateColor(primitive.GetColor());
      VerticesData vertices = primitive.GetDrawable().GetVerticesData();
      std::vector<u32> indices = primitive.GetDrawable().GetIndicesData();

      Renderer::Batch::PushObject(std::move(vertices), indices, transl_scale_comp.GetModelMat());
    }
    Renderer::Batch::End();
  }
}

Entity Scene::CreateEntity(std::string&& name)
{
  GE_PROFILE;
  Entity ent = m_registry.Create();
  GE_INFO("Creating entity \'{}\' with id={}", name, ent.handle)
  AddComponent<TagComponent>(ent, std::move(name));
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

  const std::vector<Entity> camera_entities = m_registry.Group<CameraComponent>();
  for (auto ent : camera_entities)
  {
    auto& cam_comp = m_registry.GetComponent<CameraComponent>(ent);
    if (!cam_comp.IsFixedRatio())
    {
      cam_comp.GetCamera().SetViewport(dim);
    }
  }
}

Opt<Entity> Scene::RetrieveActiveCamera() const
{
  GE_PROFILE;
  std::vector<Entity> camera_group = m_registry.Group<CameraComponent>();
  if (camera_group.empty())
  {
    GE_INFO("No camera")
    return std::nullopt;
  }

  if (std::ranges::none_of(camera_group,
                           [&](Entity ent)
                           {
                             const auto& cc = m_registry.GetComponent<CameraComponent>(ent);
                             return cc.IsActive();
                           }))
  {
    GE_INFO("No active camera")
    return std::nullopt;
  }

  if (std::ranges::count(camera_group |
                           std::views::transform(
                             [&](Entity ent) -> bool
                             { return m_registry.GetComponent<CameraComponent>(ent).IsActive(); }),
                         true) > 1)
  {
    GE_INFO("More than one active camera")
    return std::nullopt;
  }

  const Entity active_camera = *std::ranges::find_if(
    camera_group,
    [&](Entity ent) -> bool { return m_registry.GetComponent<CameraComponent>(ent).IsActive(); });

  return active_camera;
}

void Scene::EachEntity(const std::function<void(Entity)>& fun)
{
  GE_PROFILE;
  m_registry.Each(fun);
}

void Scene::SetActiveCamera(Opt<Entity> activeCamera)
{
  GE_PROFILE;
  auto cameras = m_registry.Group<CameraComponent>();
  for (const Entity& ent : cameras)
  {
    if (ent == activeCamera)
      continue;
    m_registry.GetComponent<CameraComponent>(ent).SetActive(false);
  }
  m_active_camera = activeCamera;
}

void Scene::DestroyEntity(Opt<Entity> ent)
{
  GE_PROFILE;
  m_registry.Destroy(ent);
}

void Scene::UpdateLightSourcesPosition(TimeStep& /*ts*/)
{
  GE_PROFILE;
  const std::vector<Entity> light_sources = m_registry.Group<LightSourceComponent>();
  if (light_sources.empty())
    return;

  const auto& active_camera = m_active_camera.value();

  const CameraComponent& cam_component = m_registry.GetComponent<CameraComponent>(active_camera);

  { // Reset ambient and light colors
    Renderer::SetAmbientLight(Colors::WHITE, 1.0f);
    Renderer::SetLightSources(
      std::vector<LightSource>{ { Vec3{ 0, 0, 0 }, Colors::BLACK, 0.0f, 0.5f, 32.0f } });
  }

  Renderer::Batch::Begin(cam_component.GetCamera().GetViewProjection(),
                         cam_component.GetCamera().GetPosition());
  for (auto ent : light_sources)
  {
    auto& lp = m_registry.GetComponent<LightSourceComponent>(ent);
    if (!lp.IsActive())
      continue;
    Mat4 translate = Transform::Translate(lp.GetPos()) * Transform::Scale(0.1f, 0.1f, 0.1f);
    lp.GetDrawable().UpdateColor(lp.GetColor());
    auto vertices = lp.GetDrawable().GetVerticesData();
    auto indices = lp.GetDrawable().GetIndicesData();
    Renderer::Batch::PushObject(std::move(vertices), indices, translate);
  }
  Renderer::Batch::End();

  { // Reset ambient and light colors
    Renderer::SetAmbientLight(Colors::BLACK, 0.0f);
    Renderer::SetLightSources(
      std::vector<LightSource>{ { Vec3{ 0, 0, 0 }, Colors::BLACK, 0.0f, 0.5f, 32.0f } });
  }
}
