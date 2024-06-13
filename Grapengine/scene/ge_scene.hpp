#ifndef GRAPENGINE_GE_SCENE_HPP
#define GRAPENGINE_GE_SCENE_HPP

#include "core/ge_time_step.hpp"
#include "events/ge_event.hpp"
#include "ge_ec_registry.hpp"

namespace GE
{
  class Scene
  {
  public:
    static Ptr<Scene> Make();

    Scene();

    Entity CreateEntity(std::string&& name);

    void DestroyEntity(Opt<Entity> ent);

    void OnUpdate(TimeStep ts);

    void OnEvent(Event&);

    void OnViewportResize(Dimension dim);

    void UpdateActiveCamera(Opt<Entity> activeCamera);

    // Registry wrappers functions

    template <typename Component, typename... Args>
    Component& AddComponent(const Entity& ent, Args&&... args)
    {
      GE_PROFILE;
      return m_registry.AddComponent<Component>(ent, std::forward<Args>(args)...);
    }

    template <typename Component>
    Component& GetComponent(const Entity& ent)
    {
      GE_PROFILE;
      return m_registry.GetComponent<Component>(ent);
    }

    template <typename Component>
    [[nodiscard]] bool HasComponent(const Opt<Entity>& ent)
    {
      GE_PROFILE;
      return ent ? m_registry.Has<Component>(ent.value()) : false;
    }

    template <typename Component>
    [[nodiscard]] bool HasComponent(const Entity& ent)
    {
      GE_PROFILE;
      return m_registry.Has<Component>(ent);
    }

    template <typename Component>
    void RemoveComponent(Entity ent)
    {
      if (HasComponent<Component>(ent))
        m_registry.RemoveComponent<Component>(ent);
    }

    void EachEntity(const std::function<void(Entity)>& fun) const;

  private:
    void UpdateNativeScripts(TimeStep& ts);
    void UpdateDrawableEntities(TimeStep& ts);
    void UpdateLightSpots(TimeStep& ts);

    [[nodiscard]] Opt<Entity> RetrieveActiveCamera() const;

    ECRegistry m_registry;
    Opt<Entity> m_active_camera;
    Opt<Entity> m_active_ambient_light;
    Dimension m_viewport;
  };

} // GE

#endif // GRAPENGINE_GE_SCENE_HPP
