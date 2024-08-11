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
    static Ptr<Scene> Make(const std::string& name);

    Scene(const std::string& name);

    Entity CreateEntity(std::string&& name);

    void PushEntity(Entity entity);

    void EnqueueToDestroy(Opt<Entity> ent);

    void OnUpdate(TimeStep ts);

    void OnEvent(Event&);

    void OnViewportResize(Dimension dim);

    void SetActiveCamera(Opt<Entity> activeCamera);

    // Registry wrappers functions

    template <typename Component, typename... Args>
    Component& AddComponent(const Entity& ent, Args&&... args)
    {
      GE_PROFILE;
      return m_registry.AddComponent<Component>(ent, std::forward<Args>(args)...);
    }

    template <typename Component>
    void PushComponent(const Entity& ent, Opt<Component> component)
    {
      GE_PROFILE;
      if (!component)
        return;

      return m_registry.PushComponent<Component>(ent, std::move(component.value()));
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
      return ent && m_registry.Has<Component>(ent.value());
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
    const std::set<Entity>& GetEntities() const;

    const std::vector<VarComponent>& GetComponents(const Entity& ent) const;

    const std::string& GetName() const;
    void SetName(const std::string& name);

    // [[nodiscard]] bool operator==(const Scene& other) const;
    // [[nodiscard]] bool operator!=(const Scene& other) const;

  private:
    void UpdateNativeScripts(TimeStep& ts);
    void UpdateDrawableEntities(TimeStep& ts);
    void UpdateLightSourcesPosition(TimeStep& ts);
    void UpdateActiveCamera();
    void UpdateLightSources() const;
    void UpdateAmbientLight() const;

    [[nodiscard]] Opt<Entity> RetrieveActiveCamera() const;

    std::string m_name;
    ECRegistry m_registry;
    Opt<Entity> m_active_camera;
    Opt<Entity> m_active_ambient_light;
    Dimension m_viewport;
  };

} // GE

#endif // GRAPENGINE_GE_SCENE_HPP
