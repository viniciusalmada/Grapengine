#ifndef GE_ENTRY_POINT_HPP
#define GE_ENTRY_POINT_HPP

#include "controllers/ge_app_controller.hpp"
#include "core/ge_application.hpp"
#include "core/ge_memory.hpp"
#include "ge_assert.hpp"

extern GE::Ref<GE::Application> CreateApplication();

int main(int /*argc*/, char* argv[])
{
  GE::Logger::Init();
  GE_DEBUG("----------Startup at <{}>----------", argv[0]);
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
