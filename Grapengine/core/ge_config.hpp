#ifndef GRAPENGINE_CONFIG_HPP
#define GRAPENGINE_CONFIG_HPP

#if !(defined(GE_PLATFORM_WINDOWS) || defined(GE_PLATFORM_LINUX))
  #error "Unsupported platform"
#endif

#if defined(USE_TRACY_PROFILER)
  #include <cstddef>

void* operator new(std::size_t count);

void operator delete(void* ptr) noexcept;

#endif

#endif // GRAPENGINE_CONFIG_HPP
