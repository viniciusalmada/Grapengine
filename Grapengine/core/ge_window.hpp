#ifndef GRAPENGINE_WINDOW_HPP
#define GRAPENGINE_WINDOW_HPP

#include "GLFW/glfw3.h"
#include "drawables/ge_color.hpp"
#include "events/ge_event.hpp"
#include "ge_context.hpp"
#include "log/ge_logger.hpp"
#include "math/ge_vector.hpp"
#include "utils/ge_dimension.hpp"

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
    Dimension dim;

    explicit WindowProps(std::string_view titleStr, Dimension d, std::string_view icon) :
        title(titleStr), icon_path(icon), dim(d)
    {
    }
  };

  class Window
  {
  public:
    static Ref<Window> Make(const WindowProps& props, const EventCallbackFn& cb);

    explicit Window(const WindowProps& props, const EventCallbackFn& cb);
    ~Window();

    [[deprecated("Use GetDimension")]] [[nodiscard]] u32 GetWidth() const;
    [[deprecated("Use GetDimension")]] [[nodiscard]] u32 GetHeight() const;
    [[nodiscard]] Dimension GetDimension() const;

    void SetVsync(bool enabled);

    void OnUpdate();

    [[nodiscard]] std::any GetNativeHandler() const;

  private:
    void SetupCallbacks(const EventCallbackFn& cb);

    WindowProps m_window_props;
    bool m_vsync;
    GLFWwindow* m_window;
    Context m_context;
    EventCallbackFn m_event_callback;
  };
}

#endif
