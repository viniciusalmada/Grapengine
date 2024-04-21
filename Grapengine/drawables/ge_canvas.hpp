#ifndef GRAPENGINE_CANVAS_HPP
#define GRAPENGINE_CANVAS_HPP

#include "core/ge_macros.hpp"
#include "core/ge_type_aliases.hpp"
#include "ge_drawable.hpp"

namespace GE
{
  struct Vec4;

  class Canvas
  {
  public:
    Canvas(u32 width, u32 height);

    static void Clear(const Vec4& color);
    static void Draw(const Ref<Drawable>& drawable);
  };
}

#endif // GRAPENGINE_CANVAS_HPP
