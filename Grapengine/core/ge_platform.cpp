#include "core/ge_platform.hpp"

using namespace GE;

u64 Platform::GetCurrentTimeMS()
{
  // Get the current time point
  auto now = std::chrono::system_clock::now();

  // Cast the time point to milliseconds since epoch
  auto duration = now.time_since_epoch();
  auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

  return static_cast<u64>(millis);
}
