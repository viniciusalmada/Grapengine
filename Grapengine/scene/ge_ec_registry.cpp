#include "scene/ge_ec_registry.hpp"

using namespace GE;

Entity ECRegistry::Create()
{
  Entity e{ m_entity_next_id++ };
  m_entities.insert(e);
  return e;
}

void ECRegistry::Each(const std::function<void(Entity)>& action) const
{
  std::ranges::for_each(m_entities, action);
}

std::vector<Entity> ECRegistry::Group(const std::initializer_list<CompType>&& comps) const
{
#ifdef DEBUG_ECSREGISTRY
  GE_DEBUG("BEGIN: Getting group of: ")
  (..., [] { GE_DEBUG("{}", typeid(Comps).name()); }());
  GE_DEBUG("END")
#endif

  std::vector<Entity> entities;
  for (const Entity& e :
       m_components                                                                             //
         | std::views::filter([&](auto&& p) { return FilterComponentsFromEntities(comps, p); }) //
         | std::views::keys)
  {
    entities.push_back(e);
  }
  return entities;
}
