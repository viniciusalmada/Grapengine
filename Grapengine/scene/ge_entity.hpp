#ifndef GRAPENGINE_GE_ENTITY_HPP
#define GRAPENGINE_GE_ENTITY_HPP

#include "core/ge_type_aliases.hpp"

namespace GE
{
  struct Entity
  {
    u32 handle;

    explicit Entity(u32 h);
    bool operator<(const Entity& ent) const { return handle < ent.handle; }

    bool operator==(const Entity& rhs) const { return handle == rhs.handle; }
    bool operator!=(const Entity& rhs) const { return !(rhs == *this); }
  };
}

#endif // GRAPENGINE_GE_ENTITY_HPP
