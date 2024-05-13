#ifndef GRAPENGINE_GE_SCRIPTABLE_ENTITY_HPP
#define GRAPENGINE_GE_SCRIPTABLE_ENTITY_HPP

#include "scene/ge_entity.hpp"
#include "scene/ge_scene.hpp"

namespace GE
{
  class ScriptableEntity
  {
  public:
    ScriptableEntity(Entity ent, Scene& scene);

    virtual void OnCreate() {}
    virtual void OnDestroy() {}
    virtual void OnUpdate(TimeStep /*ts*/) {}

  protected:
    Entity m_entity;
    Scene& m_scene;
  };
}

#endif // GRAPENGINE_GE_SCRIPTABLE_ENTITY_HPP
