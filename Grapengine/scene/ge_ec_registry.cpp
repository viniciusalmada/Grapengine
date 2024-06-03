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

void ECRegistry::Each(const std::function<void(Entity)>& action) const
{
  std::ranges::for_each(m_entities, action);
}

std::vector<Entity> ECRegistry::Group(const std::set<CompType>&& comps) const
{
  GE_PROFILE;

  std::vector<Entity> entities;
  for (const auto& [ent, its_comps] : m_entities_with_components)
  {
    if (std::ranges::includes(its_comps, comps))
      entities.push_back(ent);
  }
  return entities;
}

void ECRegistry::Destroy(Entity ent)
{
  m_entities.erase(ent);
  m_components.erase(ent);
  m_entities_with_components.erase(ent);
}
