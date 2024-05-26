#ifndef GE_ENTRY_POINT_HPP
#define GE_ENTRY_POINT_HPP

#include "controllers/ge_app_controller.hpp"
#include "core/ge_application.hpp"
#include "core/ge_memory.hpp"
#include "profiling/ge_profiler.hpp"

extern GE::Ref<GE::Application> CreateApplication();

namespace
{
  GE::Ref<GE::Application> Start(int argc, char* argv[]) noexcept
  {
    GE_PROFILE_SECTION("Main init");
    GE::Logger::Init();
    auto args = std::span(argv, u64(argc));
    GE_DEBUG("Main: Starting up at \'{}\'", args.front())
    auto app = CreateApplication();
    GE::Ctrl::App::Init(app);
    return app;
  }

  void Run(GE::Ref<GE::Application>& app) noexcept
  {
    GE_PROFILE_SECTION("Main running");
    GE_DEBUG("Main: Running")
    app->Run();
  }

  void Shutdown(GE::Ref<GE::Application>& app) noexcept
  {
    GE_PROFILE_SECTION("Main: Shutdown");
    GE_DEBUG("Shutdown")
    GE::Ctrl::App::Shutdown();
    app.reset();
    GE::Logger::Shutdown();
  }
}

// NOLINT(*-definitions-in-headers)
int main(int argc, char* argv[])
{
  GE::Ref<GE::Application> app = Start(argc, argv);
  Run(app);
  Shutdown(app);
}

#endif // GE_ENTRY_POINT_HPP
