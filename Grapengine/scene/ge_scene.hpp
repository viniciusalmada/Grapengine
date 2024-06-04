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

    void DestroyEntity(Entity ent);

    void OnUpdate(TimeStep ts);

    void OnEvent(Event&);

    void OnViewportResize(Dimension dim);

    void UpdateActiveCamera(Entity activeCamera);

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
    [[nodiscard]] bool HasComponent(const Entity& ent)
    {
      GE_PROFILE;
      return m_registry.Has<Component>(ent);
    }

    void EachEntity(const std::function<void(Entity)>& fun) const;

  private:
    void UpdateNativeScripts(TimeStep& ts);
    void UpdateDrawableEntities(TimeStep& ts);

    [[nodiscard]] Opt<Entity> RetrieveActiveCamera() const;

    ECRegistry m_registry;
    Opt<Entity> m_active_camera;
    Dimension m_viewport;
    std::vector<std::pair<f32, u32>> m_randoms;
    //    u64 m_random_id = 0;
  };

} // GE

#endif // GRAPENGINE_GE_SCENE_HPP
