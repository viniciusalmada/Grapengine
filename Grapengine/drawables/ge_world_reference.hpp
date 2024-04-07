#ifndef GRAPENGINE_GE_WORLD_REFERENCE_HPP
#define GRAPENGINE_GE_WORLD_REFERENCE_HPP

#include "core/ge_macros.hpp"
#include "core/ge_type_aliases.hpp"

namespace GE
{
  class IShaderProgram;

  class WorldReference
  {
  public:
    WorldReference(const Ref<IShaderProgram>& shader, u64 platformSize);
    ~WorldReference();

    void DrawBatch() const;

    void ShowPlatform(bool show) const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_GE_WORLD_REFERENCE_HPP
