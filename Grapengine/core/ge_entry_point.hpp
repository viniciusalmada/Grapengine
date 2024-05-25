#ifndef GE_ENTRY_POINT_HPP
#define GE_ENTRY_POINT_HPP

#include "controllers/ge_app_controller.hpp"
#include "core/ge_application.hpp"
#include "core/ge_memory.hpp"
#include "ge_assert.hpp"
#include "profiling/ge_profiler.hpp"

extern GE::Ref<GE::Application> CreateApplication();

// NOLINT(*-definitions-in-headers)
int main(int argc, char* argv[])
{
  GE::Ref<GE::Application> app = nullptr;
  {
    GE_PROFILE_SECTION("Main init");
    GE::Logger::Init();
    auto args = std::span(argv, u64(argc));
    GE_DEBUG("----------Startup at <{}>----------", args.front())
    app = CreateApplication();
    GE::Ctrl::App::Init(app);
  }

  {
    GE_PROFILE_SECTION("Main running");
    GE_DEBUG("----------Running----------")
    app->Run();
  }

  GE_DEBUG("----------Shutdown----------")
  {
    GE_PROFILE_SECTION("Main Shutdown");
    GE::Ctrl::App::Shutdown();
    app.reset();
    GE::Logger::Shutdown();
  }
}

#endif // GE_ENTRY_POINT_HPP
