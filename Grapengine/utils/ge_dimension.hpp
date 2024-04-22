#ifndef GRAPENGINE_GE_DIMENSION_HPP
#define GRAPENGINE_GE_DIMENSION_HPP

#include "core/ge_type_aliases.hpp"

namespace GE
{
  struct Dimension
  {
    u32 width;
    u32 height;

    [[nodiscard]] bool IsEmpty() const { return width == 0 || height == 0; }
    [[nodiscard]] bool operator==(const Dimension& rhs) const
    {
      return width == rhs.width && height == rhs.height;
    }
    [[nodiscard]] bool operator!=(const Dimension& rhs) const { return !(rhs == *this); }
  };
}

#endif // GRAPENGINE_GE_DIMENSION_HPP
