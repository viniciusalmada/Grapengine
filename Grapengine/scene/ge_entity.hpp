#ifndef GRAPENGINE_GE_ENTITY_HPP
#define GRAPENGINE_GE_ENTITY_HPP

#include "core/ge_type_aliases.hpp"

namespace GE
{
  struct Entity
  {
    u32 handle;

    bool operator<(const Entity& ent) const { return handle < ent.handle; }
  };
}

#endif // GRAPENGINE_GE_ENTITY_HPP
