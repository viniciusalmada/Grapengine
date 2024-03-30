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

#ifndef GE_ASSERT
  #if defined(GE_DIST)
    #define GE_ASSERT(...)
  #else
    #define GE_ASSERT(cond, ...)                                                                   \
      {                                                                                            \
        if (!(cond))                                                                               \
        {                                                                                          \
          GE_ERROR("Assertion failed: {0}", __VA_ARGS__)                                           \
          BREAKPOINT                                                                               \
        }                                                                                          \
      }
  #endif
#endif

#endif // GRAPENGINE_ASSERT_HPP
