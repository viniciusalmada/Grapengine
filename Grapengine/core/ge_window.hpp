#ifndef GRAPENGINE_WINDOW_HPP
#define GRAPENGINE_WINDOW_HPP

#include "GLFW/glfw3.h"
#include "core/ge_macros.hpp"
#include "drawables/ge_canvas.hpp"
#include "drawables/ge_color.hpp"
#include "events/ge_event.hpp"
#include "ge_context.hpp"
#include "log/ge_logger.hpp"
#include "math/ge_vector.hpp"

#include <any>
#include <functional>
#include <string>

namespace GE
{
  using EventCallbackFn = std::function<void(Event&)>;

  class Context;

  struct WindowProps
  {
    std::string title;
    std::string icon_path;
    u32 width;
    u32 height;

    explicit WindowProps(std::string_view titleStr, u32 w, u32 h, std::string_view icon) :
        title(titleStr), icon_path(icon), width(w), height(h)
    {
    }
  };

  class Window
  {
  public:
    static Ref<Window> Make(const WindowProps& props, const EventCallbackFn& cb);

    explicit Window(const WindowProps& props, const EventCallbackFn& cb);
    ~Window();

    [[nodiscard]] u32 GetWidth() const;
    [[nodiscard]] u32 GetHeight() const;

    void SetVsync(bool enabled);

    void OnUpdate();

    void Clear(Color color) const;
    void Draw(const Ref<Drawable>& drawable) const;

    [[nodiscard]] std::any GetNativeHandler() const;

  private:
    void SetupCallbacks(const EventCallbackFn& cb);

    WindowProps m_window_props;
    bool m_vsync;
    GLFWwindow* m_window;
    Context m_context;
    EventCallbackFn m_event_callback;
    Ref<Canvas> m_canvas;
  };
}

#endif
