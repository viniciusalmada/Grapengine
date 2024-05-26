#ifndef GRAPENGINE_GE_IMGUI_LAYER_HPP
#define GRAPENGINE_GE_IMGUI_LAYER_HPP

#include "core/ge_window.hpp"
#include "ge_layer.hpp"

namespace GE
{
  class ImGuiLayer : public Layer
  {
  public:
    static Ptr<ImGuiLayer> Make(Ptr<Window> window);
    explicit ImGuiLayer(Ptr<Window> window);
    ~ImGuiLayer() override;

    void Begin();
    void End();
    void OnAttach() override;
    void OnDetach() override;
    void OnEvent(GE::Event& /*unused*/) override;

    void AllowMouseAndKeyboardEvents(bool allow);

  private:
    Ptr<Window> m_window = nullptr;
    bool m_allow_imgui_events = false;
  };
}

#endif // GRAPENGINE_GE_IMGUI_LAYER_HPP
