#include "ge_app_controller.hpp"

#include <core/ge_assert.hpp>

using namespace GE;

namespace
{
  std::optional<Ctrl::App> ctrl_app = std::nullopt;
}

struct Ctrl::App::Impl
{
  Weak<Application> app;
};

GE::Ctrl::App::App() : m_pimpl(MakeScope<Impl>()) {}

void Ctrl::App::Init(const Ref<Application>& app)
{
  ctrl_app.emplace(App{});
  ctrl_app->m_pimpl->app = app;
}

void GE::Ctrl::App::Close()
{
  GE_ASSERT(ctrl_app.has_value(), "Controller not initialized");
  GE_ASSERT(!ctrl_app->m_pimpl->app.expired(), "Application destroyed");

  auto application = ctrl_app->m_pimpl->app.lock();
  application->Close();
}
