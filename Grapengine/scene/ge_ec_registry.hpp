#ifndef GRAPENGINE_GE_EC_REGISTRY_HPP
#define GRAPENGINE_GE_EC_REGISTRY_HPP

#include "ge_comp_types.hpp"
#include "ge_components.hpp"
#include "ge_entity.hpp"
#include "profiling/ge_profiler.hpp"

namespace GE
{
  class ECRegistry
  {
  public:
    /**
     * Create and return an entity with a unique id
     * @return empty entity
     */
    Entity Create();

    void Destroy(Entity ent);

    /**
     * Add a component to registry and associate to its entity
     * @tparam Component type of component
     * @tparam Args argument list to construct the component
     * @param ent entity that is associated of component
     * @param args argument list to construct the component
     */
    template <typename Component, typename... Args>
    Component& AddComponent(const Entity& ent, Args... args)
    {
      GE_PROFILE;
      GE_ASSERT(!Has<Component>(ent), "Entity already has this component!")

      auto& added = m_components[ent].emplace_back(MakeRef<Component>(std::forward<Args>(args)...));
      GE_ASSERT(added->Type() != CompType::BASE, "Component must not have BASE type")
      m_entities_with_components[ent].insert(added->Type());

      return dynamic_cast<Component&>(*added);
    }

    /**
     * Retrieve the component of type Comp associated with entity
     * @tparam Component component type to be got
     * @param ent entity that is associated with component
     * @return associated component
     */
    template <typename Component>
    [[nodiscard]] Component& GetComponent(const Entity& ent)
    {
      GE_PROFILE;
      GE_ASSERT(Has<Component>(ent), "Entity does not have this component!")

      auto found =
        std::ranges::find_if(m_components.at(ent),
                             [&](auto&& anyComp) { return typeid(*anyComp) == typeid(Component); });
      return dynamic_cast<Component&>(**found);
    }

    /**
     * Retrieve the component of type Comp associated with entity
     * @tparam Component component type to be got
     * @param ent entity that is associated with component
     * @return associated component
     */
    template <typename Component>
    [[nodiscard]] const Component& GetComponent(const Entity& ent) const
    {
      GE_PROFILE;
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
      GE_PROFILE;
      if (!m_entities.contains(ent))
        return false;

      if (!m_components.contains(ent))
        return false;

      if (m_components.at(ent).empty())
        return false;

      auto found = std::ranges::find_if(m_components.at(ent),
                                        [&](const Ptr<BaseComponent>& anyComp)
                                        {
                                          [[maybe_unused]] auto& comp_ref = *anyComp;
                                          return typeid(comp_ref) == typeid(Comp);
                                        });
      return found != m_components.at(ent).end();
    }

    /**
     * Retrieve list of entities that has all passed components
     * @param comps list of components used to query the entities
     * @return set of entities that has all given components in common
     */
    [[nodiscard]] std::vector<Entity> Group(const std::set<CompType>&& comps) const;

    void Each(const std::function<void(Entity)>& action) const;

  private:
    u32 m_entity_next_id = 0;
    std::set<Entity> m_entities;
    std::map<Entity, std::list<Ptr<BaseComponent>>> m_components;
    std::map<Entity, std::set<CompType>> m_entities_with_components;
  };
} // GE

#endif // GRAPENGINE_GE_EC_REGISTRY_HPP
