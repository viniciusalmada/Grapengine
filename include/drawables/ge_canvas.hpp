#ifndef GRAPHICENGINE3D_GE_CANVAS_HPP
#define GRAPHICENGINE3D_GE_CANVAS_HPP

#include "ge_drawable.hpp"
#include "ge_pch.hpp"

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

#endif // GRAPHICENGINE3D_GE_CANVAS_HPP
