#ifndef GRAPENGINE_APPLICATION_HPP
#define GRAPENGINE_APPLICATION_HPP

#include "ge_config.hpp"
#include "ge_macros.hpp"
#include "ge_type_aliases.hpp"
#include "layer/ge_imgui_layer.hpp"

#include <functional>
#include <string>

namespace GE
{
  class Window;
  class Event;
  class Layer;

  class Application
  {
  public:
    Application(std::string_view title, Dimension dim, std::string_view icon);
    virtual ~Application();

    void AddLayer(const Ref<Layer>& layer);

    void Run();

    void Close();

    void OnEvent(Event& e);

    [[nodiscard]] Ref<ImGuiLayer> GetImGuiLayer() const;

  private:
    void
    Init(std::string_view title, Dimension dim, std::string_view icon, const EventCallbackFn& cb);

    void OnDestroy();

    void Finish();

    Ref<Window> m_window;
    bool m_running = true;
    bool m_minimized = false;
    u64 m_last_frame_time{ 0 };
    std::vector<Ref<Layer>> m_layers;
    Ref<ImGuiLayer> m_imgui_layer;
  };
}

#endif
