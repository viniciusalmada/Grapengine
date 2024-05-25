#if defined(USE_TRACY_PROFILER)

  #include "profiling/ge_profiler.hpp"

  #include <cstddef>
  #include <cstdlib>

void* operator new(std::size_t count)
{
  auto ptr = std::malloc(count);
  GE_ALLOC(ptr, count)
  return ptr;
}

void operator delete(void* ptr) noexcept
{
  GE_FREE(ptr)
  free(ptr);
}

#endif
