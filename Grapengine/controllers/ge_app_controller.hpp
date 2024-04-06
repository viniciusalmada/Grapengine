#ifndef GRAPENGINE_GE_APP_CONTROLLER_HPP
#define GRAPENGINE_GE_APP_CONTROLLER_HPP

#include "core/ge_application.hpp"

namespace GE::Ctrl
{
  class App
  {
  public:
    static void Init(const Ref<GE::Application>& app);
    static void Shutdown();

    static void Close();

    static void AllowImGuiEvents(bool value);

  private:
    App();

    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}
#endif // GRAPENGINE_GE_APP_CONTROLLER_HPP
