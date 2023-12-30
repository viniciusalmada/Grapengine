#include "ge_assert.hpp"

void Assert(bool condition, const char* message)
{
  if (condition)
    return;

  std::cerr << "ASSERTION FAILED: " << message << std::endl;
#ifdef WIN32
  __debugbreak();
#elif LINUX
  asm {int3;}
#endif
}