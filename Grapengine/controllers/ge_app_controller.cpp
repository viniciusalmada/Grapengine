#include "ge_app_controller.hpp"

#include "core/ge_assert.hpp"

using namespace GE;

namespace
{
  std::optional<Ctrl::App> ctrl_app = std::nullopt;
}

GE::Ctrl::App::App() {}

void Ctrl::App::Init(const Ref<Application>& app)
{
  ctrl_app.emplace(App{});
  ctrl_app->m_application = app;
}

void GE::Ctrl::App::Shutdown()
{
  ctrl_app.reset();
}

void GE::Ctrl::App::Close()
{
  GE_ASSERT(ctrl_app.has_value(), "Controller not initialized")
  GE_ASSERT(ctrl_app->m_application != nullptr, "Application destroyed")

  ctrl_app->m_application->Close();
}
void GE::Ctrl::App::AllowImGuiEvents(bool value)
{
  GE_ASSERT(ctrl_app.has_value(), "Controller not initialized")
  GE_ASSERT(ctrl_app->m_application != nullptr, "Application destroyed")

  ctrl_app->m_application->GetImGuiLayer()->AllowMouseAndKeyboardEvents(value);
}
