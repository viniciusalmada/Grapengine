#ifndef GE_ENTRY_POINT_HPP
#define GE_ENTRY_POINT_HPP

#include "core/ge_application.hpp"
#include "core/ge_memory.hpp"

extern GE::Scope<GE::Application> CreateApplication();

int main(int argc, char* argv[])
{
  {
    auto app = CreateApplication();
    app->Run();
  }
}

#endif // GE_ENTRY_POINT_HPP
