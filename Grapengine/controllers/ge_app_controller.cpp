#include "ge_app_controller.hpp"

#include "core/ge_assert.hpp"

using namespace GE;

GE::Ctrl::App::App() {}

void Ctrl::App::Init(const Ref<Application>& app)
{
  Get().m_application = app;
}

void GE::Ctrl::App::Shutdown()
{
  Get().m_application.reset();
}

void GE::Ctrl::App::Close()
{
  GE::Assert(Get().m_application.has_value(), "Controller not initialized");
  GE::Assert(Get().m_application != nullptr, "Application destroyed");

  Get().m_application.value()->Close();
}
void GE::Ctrl::App::AllowImGuiEvents(bool value)
{
  GE::Assert(Get().m_application.has_value(), "Controller not initialized");
  GE::Assert(Get().m_application != nullptr, "Application destroyed");

  Get().m_application.value()->GetImGuiLayer()->AllowMouseAndKeyboardEvents(value);
}

Ctrl::App& Ctrl::App::Get()
{
  static App app;
  return app;
}
