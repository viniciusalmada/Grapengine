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

    static App& Get();

    std::optional<Ref<Application>> m_application = std::nullopt;
  };
}
#endif // GRAPENGINE_GE_APP_CONTROLLER_HPP
