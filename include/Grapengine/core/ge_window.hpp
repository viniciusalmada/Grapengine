#ifndef GRAPENGINE_WINDOW_HPP
#define GRAPENGINE_WINDOW_HPP

#include "core/ge_macros.hpp"
#include "drawables/ge_canvas.hpp"
#include "drawables/ge_color.hpp"
#include "events/ge_event.hpp"
#include "math/ge_vector.hpp"

#include <functional>
#include <string>

namespace GE
{
  using EventCallbackFn = std::function<void(Event&)>;

  struct WindowProps
  {
    std::string title;
    std::string icon_path;
    u32 width;
    u32 height;

    explicit WindowProps(const std::string& title, u32 w, u32 h, const std::string& icon) :
        title(title), width(w), height(h), icon_path(icon)
    {
    }
  };

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
}

#endif
