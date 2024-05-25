#ifndef GRAPENGINE_GE_PROFILER_HPP
#define GRAPENGINE_GE_PROFILER_HPP

#if defined(USE_TRACY_PROFILER)
#define PROFILING_ENABLED
  #if defined(GE_CLANG_COMPILER) || defined(GE_GCC_COMPILER)
    #define TracyFunction __PRETTY_FUNCTION__
  #elif defined(GE_MSVC_COMPILER)
    #define TracyFunction __FUNCSIG__
  #else
    #error "Unsupported compiler"
  #endif

  #include <public/tracy/Tracy.hpp>

  #define GE_PROFILE ZoneScopedS(12)
  #define GE_PROFILE_FRAME FrameMark
  #define GE_PROFILE_FRAME_START(name) FrameMarkStart(name)
  #define GE_PROFILE_FRAME_END(name) FrameMarkEnd(name)
  #define GE_PROFILE_SECTION(name) ZoneScopedN(name)

  #define GE_ALLOC(ptr, count) TracyAllocS(ptr, count, 12);
  #define GE_FREE(ptr) TracyFreeS(ptr, 12);
#else
  #define GE_PROFILE
  #define GE_PROFILE_FRAME
  #define GE_PROFILE_FRAME_START(...)
  #define GE_PROFILE_FRAME_END(...)
  #define GE_PROFILE_SECTION(...)

  #define GE_ALLOC(...)
  #define GE_FREE(...)
#endif

#endif // GRAPENGINE_GE_PROFILER_HPP
