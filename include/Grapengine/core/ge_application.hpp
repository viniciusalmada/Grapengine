#ifndef GRAPENGINE_APPLICATION_HPP
#define GRAPENGINE_APPLICATION_HPP

#include "ge_config.hpp"
#include "ge_macros.hpp"
#include "ge_type_aliases.hpp"

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
    GE3D Application(std::string&& title, u32 width, u32 height, std::string&& icon);
    GE3D virtual ~Application();

    GE3D void AddLayer(const Ref<Layer>& layer) const;

    GE3D void Run() const;

    void OnEvent(Event& e);

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif
