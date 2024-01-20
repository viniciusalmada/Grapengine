#ifndef GRAPENGINE_CANVAS_HPP
#define GRAPENGINE_CANVAS_HPP

#include "ge_drawable.hpp"

struct Vec4;

class Canvas
{
public:
  Canvas(u32 width, u32 height);
  ~Canvas();

  static void Clear(const Vec4& color) ;
  static void Draw(const Ref<Drawable>& drawable) ;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM;
};

#endif // GRAPENGINE_CANVAS_HPP
