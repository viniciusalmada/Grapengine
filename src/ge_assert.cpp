#include "core/ge_assert.hpp"

void GE::Assert(bool condition, const char* message)
{
  if (condition)
    return;

  std::cerr << "ASSERTION FAILED: " << message << std::endl;
#ifdef GE_PLATFORM_WINDOWS
  __debugbreak();
#elif GE_PLATFORM_LINUX
  __asm__("int3");
#else
  #error "Unsupported platform"
#endif
}