#ifndef GRAPENGINE_GE_EC_REGISTRY_HPP
#define GRAPENGINE_GE_EC_REGISTRY_HPP

#include "core/ge_assert.hpp"
#include "log/ge_logger.hpp"
#include "scene/ge_entity.hpp"

#include <map>
#include <ranges>
#include <set>

namespace GE
{
  class ECRegistry
  {
  public:
    Entity Create()
    {
      Entity e{ m_entity_next_id++ };
      m_entities.insert(e);
      return e;
    }

    template <typename Comp, typename... Args>
    void AddComponent(const Entity& ent, Args&&... args)
    {
      GE_ASSERT(!Has<Comp>(ent), "Entity already has this component!")

      m_components[ent].emplace_back(std::make_any<Comp>(std::forward<Args>(args)...));
    }

    template <typename Comp>
    Comp& GetComponent(const Entity& ent)
    {
      GE_ASSERT(Has<Comp>(ent), "Entity does not have this component!")

      auto found = std::ranges::find_if(m_components[ent],
                                        [](const std::any& anyComp)
                                        { return anyComp.type() == typeid(Comp); });
      return std::any_cast<Comp&>(*found);
    }
    template <typename Comp>
    [[nodiscard]] bool Has(const Entity& ent) const
    {
      if (!m_entities.contains(ent))
        return false;

      if (!m_components.contains(ent))
        return false;

      if (m_components.at(ent).empty())
        return false;

      auto found = std::ranges::find_if(m_components.at(ent),
                                        [](const std::any& anyComp)
                                        { return anyComp.type() == typeid(Comp); });
      return found != m_components.at(ent).end();
    }
    template <typename... Comps>
    std::vector<Entity> Group()
    {
      std::vector<Entity> entities;
      for (const Entity& e : m_components                                                   //
                               | std::views::filter(FilterComponentsFromEntities<Comps...>) //
                               | std::views::keys)
      {
        entities.push_back(e);
      }
      return entities;
    }

  private:
    static void
    SameType(const std::type_info& ti, const std::any& candidate, std::map<u64, bool>& checkers)
    {
      auto cand_hash = candidate.type().hash_code();
      if (checkers.contains(cand_hash) && checkers.at(cand_hash))
        return;
      checkers[candidate.type().hash_code()] = candidate.type() == ti;
    }
    template <typename... Comps>
    static bool
    FilterComponentsFromEntities(const std::pair<Entity, std::list<std::any>>& ent_comps)
    {
      std::map<u64, bool> checkers;
      for (const std::any& c : ent_comps.second)
      {
        (..., SameType(typeid(Comps), c, checkers));
      }

      return std::ranges::any_of(checkers | std::views::values, [](bool is) { return is; });
    }
    u32 m_entity_next_id = 0;
    std::set<Entity> m_entities;
    std::map<Entity, std::list<std::any>> m_components;
  };
} // GE

#endif // GRAPENGINE_GE_EC_REGISTRY_HPP
