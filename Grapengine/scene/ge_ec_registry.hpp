#ifndef GRAPENGINE_GE_EC_REGISTRY_HPP
#define GRAPENGINE_GE_EC_REGISTRY_HPP

#include "core/ge_assert.hpp"
#include "log/ge_logger.hpp"
#include "scene/ge_components.hpp"
#include "scene/ge_entity.hpp"

#include <list>
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
    template <typename Component, typename... Args>
    void AddComponent(const Entity& ent, Args... args)
    {
      GE_ASSERT(!Has<Component>(ent), "Entity already has this component!")

      auto& added = m_components[ent].emplace_back(MakeRef<Component>(std::forward<Args>(args)...));
      { //
        if (typeid(Component) != typeid(TagComponent))
        {
          GE_DEBUG("Added component of type {} to entity {}[id={}]",
                   typeid(Component).name(),
                   GetComponent<TagComponent>(ent).tag,
                   i32(ent))
        }
      } //

      GE_ASSERT(added->Type() != CompType::BASE, "Component must not have BASE type")
    }

    /**
     * Retrieve the component of type Comp associated with entity
     * @tparam Comp component type to be got
     * @param ent entity that is associated with component
     * @return associated component
     */
    template <typename Component>
    Component& GetComponent(const Entity& ent)
    {
      GE_ASSERT(Has<Component>(ent), "Entity does not have this component!")

      auto found =
        std::ranges::find_if(m_components.at(ent),
                             [&](auto&& anyComp) { return typeid(*anyComp) == typeid(Component); });
      return dynamic_cast<Component&>(**found);
    }

    /**
     * Retrieve the component of type Comp associated with entity
     * @tparam Comp component type to be got
     * @param ent entity that is associated with component
     * @return associated component
     */
    template <typename Component>
    [[nodiscard]] const Component& GetComponent(const Entity& ent) const
    {
      GE_ASSERT(Has<Component>(ent), "Entity does not have this component!")

      auto found =
        std::ranges::find_if(m_components.at(ent),
                             [&](auto&& anyComp) { return typeid(*anyComp) == typeid(Component); });
      return dynamic_cast<const Component&>(**found);
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
                                        [&](const Ref<BaseComponent>& anyComp)
                                        {
                                          GE_DEBUG("any: {}", typeid(*anyComp).name())
                                          GE_DEBUG("template: {}", typeid(Comp).name())
                                          return typeid(*anyComp) == typeid(Comp);
                                        });
      return found != m_components.at(ent).end();
    }

    /**
     * Retrieve list of entities that has all passed components
     * @tparam Comps list of components used to query the entities
     * @return set of entities that has all given components in common
     */
    [[nodiscard]] std::vector<Entity> Group(std::initializer_list<CompType>&& comps) const
    {
#ifdef DEBUG_ECSREGISTRY
      GE_DEBUG("BEGIN: Getting group of: ")
      (..., [] { GE_DEBUG("{}", typeid(Comps).name()); }());
      GE_DEBUG("END")
#endif

      std::vector<Entity> entities;
      for (const Entity& e :
           m_components //
             |
             std::views::filter([&](auto&& p) { return FilterComponentsFromEntities(comps, p); }) //
             | std::views::keys)
      {
        entities.push_back(e);
      }
      return entities;
    }

    void Each(const std::function<void(Entity)>& action) const;

  private:
    static bool
    FilterComponentsFromEntities(const std::initializer_list<CompType>& comps,
                                 const std::pair<Entity, std::list<Ref<BaseComponent>>>& ent_comps)
    {
#ifdef DEBUG_ECSREGISTRY
      GE_DEBUG("BEGIN: Getting group of: ")
      (..., [] { GE_DEBUG("{}", typeid(Comps).name()); }());
      GE_DEBUG("END")

      std::ranges::for_each(ent_comps.second, [](auto&& a) { GE_DEBUG("{}", a.type().name()) });
#endif

      std::map<CompType, bool> checkers;
      for (const CompType& required_comp : comps)
      {
        checkers[required_comp] = std::ranges::find_if(ent_comps.second,
                                                       [&](auto&& candidate) {
                                                         return candidate->Type() == required_comp;
                                                       }) != ent_comps.second.end();
      }

      return std::ranges::all_of(checkers | std::views::values, [](bool is) { return is; });
    }

    u32 m_entity_next_id = 0;
    std::set<Entity> m_entities;
    std::map<Entity, std::list<Ref<BaseComponent>>> m_components;
  };
} // GE

#endif // GRAPENGINE_GE_EC_REGISTRY_HPP
