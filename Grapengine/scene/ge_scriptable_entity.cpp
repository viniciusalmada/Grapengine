#include "ge_scriptable_entity.hpp"

#include <utility>

using namespace GE;

ScriptableEntity::ScriptableEntity(Entity ent, Scene& scene) : m_entity(ent), m_scene(scene) {}

ScriptableEntity::~ScriptableEntity() = default;
