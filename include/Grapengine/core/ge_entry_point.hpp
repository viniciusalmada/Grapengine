#ifndef GE_ENTRY_POINT_HPP
#define GE_ENTRY_POINT_HPP

#include "core/ge_application.hpp"
#include "core/ge_memory.hpp"

extern GE::Scope<GE::Application> CreateApplication();

int main(int /*argc*/, char* argv[])
{
  GE::Logger::Init();
  GE_DEBUG("----------Startup at <{}>----------", argv[0]);
  auto app = CreateApplication();

  GE_DEBUG("----------Running----------")
  app->Run();

  GE_DEBUG("----------Shutdown----------")
  auto* ptr = app.release();
  delete ptr;
  GE::Logger::Shutdown();
}

#endif // GE_ENTRY_POINT_HPP
