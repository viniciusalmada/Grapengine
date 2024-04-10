#ifndef GRAPENGINE_GE_SCENE_HPP
#define GRAPENGINE_GE_SCENE_HPP

#include "core/ge_time_step.hpp"
#include "events/ge_event.hpp"

namespace GE
{

  struct Entity
  {
    u32 id;

    bool operator<(const Entity& rhs) const { return id < rhs.id; }
  };

  class Scene
  {
  public:
    static Ref<Scene> Make();

    Scene();
    ~Scene();

    Entity CreateEntity();

    void AddComponent(Entity ent, std::any comp);

    void OnUpdate(TimeStep ts);

    void OnEvent(Event&);

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };

} // GE

#endif // GRAPENGINE_GE_SCENE_HPP
