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
    static Ref<Scene> Make();

    Scene();

    ECRegistry& Registry();

    Entity CreateEntity(const char* name);

    template <typename Component, typename... Args>
    Component& AddComponent(const Entity& ent, Args&&... args)
    {
      return m_registry.AddComponent<Component>(ent, std::forward<Args>(args)...);
    }

    template <typename Component>
    Component& GetComponent(const Entity& ent)
    {
      return m_registry.GetComponent<Component>(ent);
    }

    void OnUpdate(TimeStep ts);

    void OnEvent(Event&);

    void OnViewportResize(Dimension dim);

  private:
    [[nodiscard]] Opt<Entity> GetActiveCamera() const;

    ECRegistry m_registry;
    Dimension m_viewport;
  };

} // GE

#endif // GRAPENGINE_GE_SCENE_HPP
