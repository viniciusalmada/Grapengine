#include "ge_scene.hpp"

#include "events/ge_event.hpp"
#include "math/ge_vector.hpp"
#include "renderer/ge_renderer.hpp"
#include "scene/ge_components.hpp"

#include <entt/entt.hpp>
#include <utility>

using namespace GE;

#define MY_ECS

#if defined(MY_ECS)

void SameType(const std::type_info& ti, const std::any& candidate, std::map<u64, bool>& checkers)
{
  auto cand_hash = candidate.type().hash_code();
  if (checkers.contains(cand_hash) && checkers.at(cand_hash))
    return;
  checkers[candidate.type().hash_code()] = candidate.type() == ti;
}

template <typename... Comps>
bool FilterComponentsFromEntities(const std::pair<GE::Entity, std::list<std::any>>& ent_comps)
{
  std::map<u64, bool> checkers;
  for (const std::any& c : ent_comps.second)
  {
    (..., SameType(typeid(Comps), c, checkers));
  }

  return std::ranges::all_of(checkers | std::views::values, [](bool is) { return is; });
};

class ECSRegistry
{
public:
  Entity Create()
  {
    auto e = Entity(m_entity_next_id++);
    m_entities.insert(e);
    return e;
  }

  template <typename Comp>
  void Emplace(Entity ent, Comp comp)
  {
    m_components[ent].push_back(comp);
  }

  template <typename Comp>
  Comp& Get(Entity ent)
  {
    auto found =
      std::ranges::find_if(m_components[ent],
                           [](const std::any& anyComp) { return anyComp.type() == typeid(Comp); });
    return std::any_cast<Comp&>(*found);
  }

  template <typename Comp>
  bool Has(Entity ent)
  {
    auto found =
      std::ranges::find_if(m_components[ent],
                           [](const std::any& anyComp) { return anyComp.type() == typeid(Comp); });
    return found != m_components[ent].end();
  }

  template <typename... Comps>
  std::vector<GE::Entity> Group()
  {
    std::vector<GE::Entity> entities;
    for (GE::Entity e : m_components                                                   //
                          | std::views::filter(FilterComponentsFromEntities<Comps...>) //
                          | std::views::keys)
    {
      entities.push_back(e);
    }
    return entities;
  }

private:
  u32 m_entity_next_id = 0;
  std::set<Entity> m_entities;
  std::map<Entity, std::list<std::any>> m_components;
};
#endif

struct Scene::Impl
{
#if defined(MY_ECS)
  ECSRegistry registry;
#endif
  entt::registry entt_reg;

  auto Create() -> Entity { return registry.Create(); }
};

Scene::Scene() : m_pimpl(MakeScope<Impl>())
{
  // #if defined(MY_ECS)
  //   {
  //     auto ent = m_pimpl->registry.Create();
  //     m_pimpl->registry.Emplace(ent, TransformComponent{});
  //
  //     if (m_pimpl->registry.Has<TransformComponent>(ent))
  //       TransformComponent& tc = m_pimpl->registry.Get<TransformComponent>(ent);
  //
  //     auto view = m_pimpl->registry.View<TransformComponent>();
  //     for (auto ent : view)
  //     {
  //       TransformComponent& c = m_pimpl->registry.Get<TransformComponent>(ent);
  //       GE_INFO("Ent: {}", ent.id);
  //     }
  //
  //     GE_INFO("")
  //   }
  // #endif
  //   {
  //     entt::entity ent = m_pimpl->entt_reg.create();
  //     [[maybe_unused]] auto comp1 = m_pimpl->entt_reg.emplace<TransformComponent>(ent);
  //     [[maybe_unused]] auto comp2 = m_pimpl->entt_reg.emplace<MeshComponent>(ent);
  [[maybe_unused]] auto group = m_pimpl->entt_reg.group<Component::Transform, Component::Primitive>(
    entt::get<Component::Primitive>);
  //     for (entt::entity e : group)
  //     {
  //       GE_INFO("{}", (u32)e)
  //     }
  //
  //     GE_INFO("")
  //   }
}

void GE::Scene::OnUpdate(TimeStep ts)
{
  auto cam_ent = m_pimpl->registry.Group<Component::EditorCamera>();
  auto cam = m_pimpl->registry.Get<Component::EditorCamera>(cam_ent.front());

  cam.cam->OnUpdate(ts);

  auto g =
    m_pimpl->registry.Group<Component::Transform, Component::Primitive, Component::ColorOnly>();
  for (auto ent : g)
  {
    Component::ColorOnly shader = m_pimpl->registry.Get<Component::ColorOnly>(ent);
    shader.shader->Activate();
    shader.shader->UpdateViewProjectionMatrix(cam.cam->GetViewProjection());

    Component::Transform model_mat = m_pimpl->registry.Get<Component::Transform>(ent);
    shader.shader->UpdateModelMatrix(model_mat.model);

    Component::Primitive primitive = m_pimpl->registry.Get<Component::Primitive>(ent);
    Renderer::DrawObject(primitive.drawing_obj);
  }
}

Entity GE::Scene::CreateEntity()
{
  return m_pimpl->registry.Create();
}

void GE::Scene::AddComponent(Entity ent, std::any comp)
{
  m_pimpl->registry.Emplace(ent, std::move(comp));
}

Ref<Scene> GE::Scene::Make()
{
  return MakeRef<Scene>();
}

void Scene::OnEvent(Event& ev)
{
  auto cam_ent = m_pimpl->registry.Group<Component::EditorCamera>();
  auto cam = m_pimpl->registry.Get<Component::EditorCamera>(cam_ent.front());

  cam.cam->OnEvent(ev);
}

Scene::~Scene() = default;
