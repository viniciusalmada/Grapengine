#include "scene/ge_ec_registry.hpp"

#include "profiling/ge_profiler.hpp"

using namespace GE;

Entity ECRegistry::Create()
{
  GE_PROFILE;
  Entity e{ m_entity_next_id++ };
  m_entities.insert(e);
  return e;
}

void ECRegistry::Push(Entity ent)
{
  auto [it, inserted] = m_entities.insert(ent);
  GE_ASSERT_OR_RETURN_VOID(inserted, "Entity already exists");

  auto max_id = std::ranges::max_element(m_entities);
  m_entity_next_id = u32(max_id->handle + 1);
}

void ECRegistry::Each(const std::function<void(Entity)>& action) const
{
  std::ranges::for_each(m_entities, action);
}

// bool ECRegistry::operator==(const ECRegistry& other) const
// {
//   return m_entities == other.m_entities                                    //
//          && m_entities_with_components == other.m_entities_with_components //
//          && m_components == other.m_components;
// }

void ECRegistry::Each(const std::function<void(Entity)>& action)
{
  m_in_loop = true;
  std::ranges::for_each(m_entities, action);
  m_in_loop = false;
  std::ranges::for_each(m_destroy_queue, [&](auto&& e) { Destroy(e); });
}

void ECRegistry::Destroy(Opt<Entity> ent)
{
  if (!ent)
    return;

  if (!m_in_loop)
  {
    m_entities.erase(ent.value());
    m_components.erase(ent.value());
    m_entities_with_components.erase(ent.value());
    return;
  }

  m_destroy_queue.insert(ent.value());
}

const std::vector<VarComponent>& ECRegistry::GetComponents(const Entity& ent) const
{
  GE_ASSERT(m_components.contains(ent), "Entity not found!");

  return m_components.at(ent);
}

const std::set<Entity>& ECRegistry::GetEntities() const
{
  return m_entities;
}
