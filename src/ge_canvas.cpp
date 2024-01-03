#include "drawables/ge_canvas.hpp"

#include <ge_vector.hpp>
#include <renderer/ge_renderer.hpp>

struct Canvas::Impl
{
  u32 width;
  u32 height;
};

Canvas::Canvas(u32 width, u32 height) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->width = width;
  m_pimpl->height = height;
}

Canvas::~Canvas() = default;

void Canvas::Clear(const Vec4& color)
{
  Renderer::SetClearColor(color);
  Renderer::Clear();
}

void Canvas::Draw(const Ref<Drawable>& drawable)
{
  drawable->Draw();
}
