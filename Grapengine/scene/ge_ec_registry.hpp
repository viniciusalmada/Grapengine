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
    /**
     * Create and return an entity with a unique id
     * @return empty entity
     */
    Entity Create()
    {
      Entity e{ m_entity_next_id++ };
      m_entities.insert(e);
      return e;
    }

    /**
     * Add a component to registry and associate to its entity
     * @tparam Comp type of component
     * @tparam Args argument list to construct the component
     * @param ent entity that is associated of component
     * @param args argument list to construct the component
     */
    template <typename Comp, typename... Args>
    void AddComponent(const Entity& ent, Args&&... args)
    {
      GE_ASSERT(!Has<Comp>(ent), "Entity already has this component!")

      m_components[ent].emplace_back(std::make_any<Comp>(std::forward<Args>(args)...));
    }

    /**
     * Retrieve the component of type Comp associated with entity
     * @tparam Comp component type to be got
     * @param ent entity that is associated with component
     * @return associated component
     */
    template <typename Comp>
    Comp& GetComponent(const Entity& ent)
    {
      GE_ASSERT(Has<Comp>(ent), "Entity does not have this component!")

      auto found = std::ranges::find_if(m_components[ent],
                                        [](const std::any& anyComp)
                                        { return anyComp.type() == typeid(Comp); });
      return std::any_cast<Comp&>(*found);
    }

    /**
     * Verify if associated component exist with given entity
     * @tparam Comp component type to be verified
     * @param ent entity associated
     * @return true if entity has the component
     */
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

    /**
     * Retrieve list of entities that has all passed components
     * @tparam Comps list of components used to query the entities
     * @return set of entities that has all given components in common
     */
    template <typename... Comps>
    [[nodiscard]] std::vector<Entity> Group() const
    {
#ifdef DEBUG_ECSREGISTRY
      GE_DEBUG("BEGIN: Getting group of: ")
      (..., [] { GE_DEBUG("{}", typeid(Comps).name()); }());
      GE_DEBUG("END")
#endif

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
    static void SameType(const std::type_info& requester,
                         const std::any& candidate,
                         std::map<u64, bool>& checkers)
    {
#ifdef DEBUG_ECSREGISTRY
      GE_DEBUG("Comp {}, Candidate {}", requester.name(), candidate.type().name())
#endif
      auto req_hash = requester.hash_code();
      if (checkers.contains(req_hash) && checkers.at(req_hash))
        return;
      checkers[req_hash] = candidate.type() == requester;
    }

    template <typename... Comps>
    static bool
    FilterComponentsFromEntities(const std::pair<Entity, std::list<std::any>>& ent_comps)
    {
#ifdef DEBUG_ECSREGISTRY
      GE_DEBUG("BEGIN: Getting group of: ")
      (..., [] { GE_DEBUG("{}", typeid(Comps).name()); }());
      GE_DEBUG("END")

      std::ranges::for_each(ent_comps.second, [](auto&& a) { GE_DEBUG("{}", a.type().name()) });
#endif

      std::map<u64, bool> checkers;
      for (const std::any& c : ent_comps.second)
      {
        (..., SameType(typeid(Comps), c, checkers));
      }

      return std::ranges::all_of(checkers | std::views::values, [](bool is) { return is; });
    }

    u32 m_entity_next_id = 0;
    std::set<Entity> m_entities;
    std::map<Entity, std::list<std::any>> m_components;
  };
} // GE

#endif // GRAPENGINE_GE_EC_REGISTRY_HPP
