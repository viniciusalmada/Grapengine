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
    Application(std::string_view title, u32 width, u32 height, std::string_view icon);
    virtual ~Application();

    void AddLayer(const Ref<Layer>& layer) const;

    void Run() const;

    void Close() const;

    void OnEvent(Event& e);

    [[nodiscard]] Ref<ImGuiLayer> GetImGuiLayer() const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif
