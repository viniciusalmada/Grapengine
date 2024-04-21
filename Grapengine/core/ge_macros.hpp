#ifndef GE_MACROS_HPP
#define GE_MACROS_HPP

// Warning disables
// clang-format off
#if defined(GE_MSVC_COMPILER)
  #define DISABLE_WARNING_PUSH __pragma(warning(push))
  #define DISABLE_WARNING_POP __pragma(warning(pop))
  #define DISABLE_WARNING(number) __pragma(warning(disable : number)) // NOLINT(*-macro-parentheses)
  #define WARN_CONVERSION_OF_GREATER_SIZE DISABLE_WARNING(4312)
  #define WARN_UNSAFE_BUFFER
#elif defined(GE_GCC_COMPILER)
  #define DISABLE_WARNING_PUSH _Pragma("GCC diagnostic push")
  #define DISABLE_WARNING_POP _Pragma("GCC diagnostic pop")
  #define DISABLE_WARNING(name) _Pragma(GCC diagnostic ignored #name)
  #define WARN_CONVERSION_OF_GREATER_SIZE
  #define WARN_UNSAFE_BUFFER
#elif defined(GE_CLANG_COMPILER) && defined(GE_PLATFORM_WINDOWS)
  #define DISABLE_WARNING_PUSH __pragma(clang diagnostic push)
  #define DISABLE_WARNING_POP __pragma(clang diagnostic pop)
  #define DISABLE_WARNING(name) __pragma(clang diagnostic ignored #name)
  #define WARN_CONVERSION_OF_GREATER_SIZE
  #define WARN_UNSAFE_BUFFER DISABLE_WARNING(-Wunsafe-buffer-usage)
#elif defined(GE_CLANG_COMPILER) && defined(GE_PLATFORM_LINUX)
  #define DISABLE_WARNING_PUSH _Pragma("clang diagnostic push")
  #define DISABLE_WARNING_POP _Pragma("clang diagnostic pop")
  #define DISABLE_WARNING(name) _pragma(clang diagnostic ignored #name)
  #define WARN_CONVERSION_OF_GREATER_SIZE
  #define WARN_UNSAFE_BUFFER
#else
  #error "Unknown compiler"
#endif
// clang-format on

#endif // GE_MACROS_HPP
