#ifndef GRAPENGINE_GE_WORLD_REFERENCE_HPP
#define GRAPENGINE_GE_WORLD_REFERENCE_HPP

#include "core/ge_macros.hpp"
#include "core/ge_type_aliases.hpp"

namespace GE
{
  class WorldReference
  {
  public:
    GE3D WorldReference();
    GE3D ~WorldReference();

    GE3D void DrawBatch() const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_GE_WORLD_REFERENCE_HPP
