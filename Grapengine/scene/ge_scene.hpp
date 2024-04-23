#ifndef GRAPENGINE_GE_SCENE_HPP
#define GRAPENGINE_GE_SCENE_HPP

#include "core/ge_time_step.hpp"
#include "events/ge_event.hpp"
#include "scene/ge_ec_registry.hpp"
#include "scene/ge_entity.hpp"
#include "utils/ge_dimension.hpp"

namespace GE
{
  class Scene
  {
  public:
    static Ref<Scene> Make();

    Scene();

    Entity CreateEntity(std::string_view name);

    template <typename Comp, typename... Args>
    void AddComponent(const Entity& ent, Args&&... args)
    {
      m_registry.AddComponent<Comp>(ent, std::forward<Args>(args)...);
    }

    template <typename Comp>
    Comp& GetComponent(const Entity& ent)
    {
      return m_registry.GetComponent<Comp>(ent);
    }

    void OnUpdate(TimeStep ts);

    void OnEvent(Event&);

    void OnViewportResize(Dimension dim);

  private:
    ECRegistry m_registry;
    Dimension m_viewport;
  };

} // GE

#endif // GRAPENGINE_GE_SCENE_HPP
