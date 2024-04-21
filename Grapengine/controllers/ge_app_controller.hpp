#ifndef GRAPENGINE_GE_APP_CONTROLLER_HPP
#define GRAPENGINE_GE_APP_CONTROLLER_HPP

#include "core/ge_application.hpp"

namespace GE::Ctrl
{
  class App
  {
  public:
    static void Init(const Ref<Application>& app);
    static void Shutdown();

    static void Close();

    static void AllowImGuiEvents(bool value);

  private:
    App() = default;

    static App& Get();

    Ref<Application> m_application = nullptr;
  };
}
#endif // GRAPENGINE_GE_APP_CONTROLLER_HPP
