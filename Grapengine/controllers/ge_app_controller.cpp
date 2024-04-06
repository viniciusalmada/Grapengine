#include "ge_app_controller.hpp"

#include <core/ge_assert.hpp>

using namespace GE;

namespace
{
  std::optional<Ctrl::App> ctrl_app = std::nullopt;
}

struct Ctrl::App::Impl
{
  void Init(const Ref<Application>& app) { application = app; }

  void Close()
  {
    GE_ASSERT(ctrl_app.has_value(), "Controller not initialized");
    GE_ASSERT(application != nullptr, "Application destroyed");

    application->Close();
  }

  void AllowImGuiEvents(bool value)
  {
    GE_ASSERT(ctrl_app.has_value(), "Controller not initialized");
    GE_ASSERT(application != nullptr, "Application destroyed");

    application->GetImGuiLayer()->AllowMouseAndKeyboardEvents(value);
  }

private:
  Ref<Application> application = nullptr;
};

GE::Ctrl::App::App() : m_pimpl(MakeScope<Impl>()) {}

void Ctrl::App::Init(const Ref<Application>& app)
{
  ctrl_app.emplace(App{});
  ctrl_app->m_pimpl->Init(app);
}

void GE::Ctrl::App::Shutdown()
{
  ctrl_app.reset();
}

void GE::Ctrl::App::Close()
{
  ctrl_app->m_pimpl->Close();
}
void GE::Ctrl::App::AllowImGuiEvents(bool value)
{
  ctrl_app->m_pimpl->AllowImGuiEvents(value);
}
