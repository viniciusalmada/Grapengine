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

void ECRegistry::Destroy(Opt<Entity> ent)
{
  if (!ent)
    return;
  m_entities.erase(ent.value());
  m_components.erase(ent.value());
  m_entities_with_components.erase(ent.value());
}
