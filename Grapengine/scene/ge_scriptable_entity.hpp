#ifndef GRAPENGINE_GE_SCRIPTABLE_ENTITY_HPP
#define GRAPENGINE_GE_SCRIPTABLE_ENTITY_HPP

#include "ge_entity.hpp"
#include "ge_scene.hpp"

namespace GE
{
  class ScriptableEntity
  {
  public:
    ScriptableEntity(Entity ent, Scene& scene);

  protected:
    Entity m_entity;
    Scene& m_scene;
  };
}

#endif // GRAPENGINE_GE_SCRIPTABLE_ENTITY_HPP
