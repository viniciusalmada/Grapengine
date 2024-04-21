#ifndef GRAPENGINE_GE_SCENE_HPP
#define GRAPENGINE_GE_SCENE_HPP

#include "core/ge_time_step.hpp"
#include "events/ge_event.hpp"
#include "ge_ec_registry.hpp"
#include "scene/ge_entity.hpp"

namespace GE
{
  class Scene
  {
  public:
    static Ref<Scene> Make();

    Scene();
    ~Scene();

    Entity CreateEntity(std::string_view name);

    template <typename Comp, typename... Args>
    void AddComponent(const Entity& ent, Args&&... args)
    {
      m_registry.AddComponent<Comp>(ent, std::forward<Args>(args)...);
    }

    void OnUpdate(TimeStep ts);

    void OnEvent(Event&);

    void OnResize(u32 w, u32 h);

  private:
    ECRegistry m_registry;
  };

} // GE

#endif // GRAPENGINE_GE_SCENE_HPP
