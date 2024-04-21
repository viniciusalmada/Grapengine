#include "drawables/ge_canvas.hpp"

#include <math/ge_vector.hpp>
#include <renderer/ge_renderer.hpp>

using namespace GE;

Canvas::Canvas(u32 /*width*/, u32 /*height*/){ GE_INFO("Canvas creation") }

void Canvas::Clear(const Vec4& color)
{
  Renderer::SetClearColor(color);
  Renderer::Clear();
}

void Canvas::Draw(const Ref<Drawable>& drawable)
{
  drawable->Draw();
}
