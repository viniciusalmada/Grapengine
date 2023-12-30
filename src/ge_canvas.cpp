#include "ge_canvas.hpp"

#include <ge_renderer.hpp>
#include <ge_vector.hpp>

struct Canvas::Impl
{
  u32 width;
  u32 height;
};

Canvas::Canvas(u32 width, u32 height) : m_pimpl(std::make_unique<Impl>())
{
  m_pimpl->width = width;
  m_pimpl->height = height;
}

Canvas::~Canvas() = default;

void Canvas::Clear(const Vec4& color) const
{
  Renderer::SetClearColor(color);
  Renderer::Clear();
}

void Canvas::Draw(Ref<Drawable> drawable) const
{
  drawable->Draw();
}
