#ifndef GRAPHIC_ENGINE3D_GE_WINDOW_HPP
#define GRAPHIC_ENGINE3D_GE_WINDOW_HPP

#include "ge_canvas.hpp"
#include "ge_event.hpp"

struct WindowProps
{
  std::string title;
  u32 width;
  u32 height;

  explicit WindowProps(std::string title = "Graphic Engine", u32 w = 1280, u32 h = 720) :
      title(std::move(title)), width(w), height(h)
  {
  }
};

using EventCallbackFn = std::function<void(Event&)>;

class Window
{
public:
  GE3D explicit Window(const WindowProps& props, const EventCallbackFn& cb);
  GE3D ~Window();

  [[nodiscard]] GE3D u32 GetWidth() const;
  [[nodiscard]] GE3D u32 GetHeight() const;

  void SetVsync(bool enabled);

  void OnUpdate();

  GE3D void Clear(const Vec4& color = Vec4(0.0, 0.0, 0.0, 1.0f)) const;
  GE3D void Draw(Ref<Drawable> drawable) const;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif
