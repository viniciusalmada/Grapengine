#ifndef GRAPENGINE_GE_ENTITY_HPP
#define GRAPENGINE_GE_ENTITY_HPP

#include "core/ge_type_aliases.hpp"

namespace GE
{
  struct Entity
  {
    i32 handle;

    Entity() : handle(-1) {}
    Entity(u32 h) : handle(i32(h)) {}
    bool operator<(const Entity& ent) const { return handle < ent.handle; }
    operator bool() const { return handle >= 0; }
    explicit operator i32() const { return handle; }

    bool operator==(const Entity& rhs) const { return handle == rhs.handle; }
    bool operator!=(const Entity& rhs) const { return !(rhs == *this); }
  };
}

#endif // GRAPENGINE_GE_ENTITY_HPP
