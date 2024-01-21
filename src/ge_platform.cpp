#include "core/ge_platform.hpp"

#include <GLFW/glfw3.h>

using namespace GE;

u64 Platform::GetCurrentTimeMS()
{
#ifdef WIN32
  FILETIME ft;
  GetSystemTimeAsFileTime(&ft);

  ULARGE_INTEGER uli;
  uli.LowPart = ft.dwLowDateTime;
  uli.HighPart = ft.dwHighDateTime;

  // Convert file time to milliseconds
  u64 curr_ms = uli.QuadPart / 10000;
  return curr_ms;
#else
  return -1;
#endif
}
