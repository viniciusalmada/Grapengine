#ifndef GRAPENGINE_WINDOW_HPP
#define GRAPENGINE_WINDOW_HPP

#include "drawables/ge_canvas.hpp"
#include "events/ge_event.hpp"
#include "math/ge_vector.hpp"

#include <drawables/ge_color.hpp>

struct WindowProps
{
  std::string title;
  u32 width;
  u32 height;

  explicit WindowProps(std::string title = "Grapengine", u32 w = 1280, u32 h = 720) :
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

  GE3D void Clear(Color color) const;
  GE3D void Draw(Ref<Drawable> drawable) const;

  Vec2 GetCursorPos() const;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif
