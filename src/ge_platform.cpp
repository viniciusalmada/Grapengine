#include "core/ge_platform.hpp"

#if defined(GE_PLATFORM_WINDOWS)
  #include <Windows.h>
#endif

using namespace GE;

u64 Platform::GetCurrentTimeMS()
{
#if defined(GE_PLATFORM_WINDOWS)
  FILETIME ft;
  GetSystemTimeAsFileTime(&ft);

  ULARGE_INTEGER uli;
  uli.LowPart = ft.dwLowDateTime;
  uli.HighPart = ft.dwHighDateTime;

  // Convert file time to milliseconds
  u64 curr_ms = uli.QuadPart / 10000;
  return curr_ms;
#elif defined(GE_PLATFORM_LINUX)
  struct timespec ts
  {
  };
  clock_gettime(CLOCK_REALTIME, &ts);
  const u64 ms =
    (static_cast<u64>(ts.tv_sec) * 1000ul + (static_cast<u64>(ts.tv_nsec) / 1'000'000ul));
  return ms;
#else
  #error "Unsupported platform"
#endif
}
