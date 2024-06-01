#ifndef GRAPENGINE_GE_COMP_TYPES_HPP
#define GRAPENGINE_GE_COMP_TYPES_HPP

#include "core/ge_type_aliases.hpp"

namespace GE
{
  enum class CompType : u8
  {
    BASE,
    TAG,
    TRANF,
    TRANSL_SCALE,
    PRIMITIVE,
    CUBE,
    MATERIAL,
    COLOR_ONLY,
    CAMERA,
    NATIVE_SCRIPT,
  };
}

#endif // GRAPENGINE_GE_COMP_TYPES_HPP
