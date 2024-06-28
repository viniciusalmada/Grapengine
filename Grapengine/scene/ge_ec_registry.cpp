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
