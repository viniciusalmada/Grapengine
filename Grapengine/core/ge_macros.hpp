#ifndef GE_MACROS_HPP
#define GE_MACROS_HPP

// Warning disables
#if defined(_MSC_VER)
  #define DISABLE_WARNING_PUSH __pragma(warning(push))
  #define DISABLE_WARNING_POP __pragma(warning(pop))
  #define DISABLE_WARNING(number) __pragma(warning(disable : number)) // NOLINT(*-macro-parentheses)
#elif defined(__GNUC__) || defined(__clang__)
  #define DISABLE_WARNING_PUSH _Pragma("GCC diagnostic push")
  #define DISABLE_WARNING_POP _Pragma("GCC diagnostic pop")
  #define DISABLE_WARNING(name) _Pragma(GCC diagnostic ignored #name)
#endif

#define POINTER_TO_IMPLEMENTATION_IDIOM                                                            \
  struct Impl;                                                                                     \
  Scope<Impl> m_pimpl;

#endif // GE_MACROS_HPP
