#ifndef GRAPENGINE_ASSERT_HPP
#define GRAPENGINE_ASSERT_HPP

#ifndef BREAKPOINT
  #ifdef GE_PLATFORM_WINDOWS
    #define BREAKPOINT __debugbreak();
  #elif GE_PLATFORM_LINUX
    #define BREAKPOINT __asm__("int3");
  #else
    #error "Unsupported platform"
  #endif
#endif

namespace GE
{
  template <typename... Args>
  void Assert(bool condition, Args... args)
  {
    if (condition)
      return;

    GE_ERROR(std::forward<Args>(args)...)
  }
}

#endif // GRAPENGINE_ASSERT_HPP
