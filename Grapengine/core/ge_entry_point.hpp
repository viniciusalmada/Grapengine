#ifndef GE_ENTRY_POINT_HPP
#define GE_ENTRY_POINT_HPP

#include "controllers/ge_app_controller.hpp"
#include "core/ge_application.hpp"
#include "core/ge_memory.hpp"
#include "ge_assert.hpp"

extern GE::Ref<GE::Application> CreateApplication();

// NOLINT(*-definitions-in-headers)
int main(int argc, char* argv[])
{
  auto args = std::span(argv, u64(argc));

  GE::Logger::Init();
  GE_DEBUG("----------Startup at <{}>----------", args.front())
  auto app = CreateApplication();
  GE::Ctrl::App::Init(app);

  GE_DEBUG("----------Running----------")
  app->Run();

  GE_DEBUG("----------Shutdown----------")
  GE::Ctrl::App::Shutdown();
  app.reset();
  GE::Logger::Shutdown();
}

#endif // GE_ENTRY_POINT_HPP
