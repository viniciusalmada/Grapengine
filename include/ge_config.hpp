#ifndef GRAPHIC_ENGINE3D_GE_CONFIG_HPP
#define GRAPHIC_ENGINE3D_GE_CONFIG_HPP

#if defined(GraphicEngine3D_EXPORTS)
  #define GE3D __declspec(dllexport)
#else
  #define GE3D __declspec(dllimport)
#endif

#if defined(_MSC_VER)
  #define DISABLE_WARNING_PUSH __pragma(warning(push))
  #define DISABLE_WARNING_POP __pragma(warning(pop))
  #define DISABLE_WARNING(number) __pragma(warning(disable : number))

  #define DISABLE_UNREACHABLE_CODE DISABLE_WARNING(4715)
#elif defined(__GNUC__) || defined(__clang__)
  #define DISABLE_WARNING_PUSH _Pragma(GCC diagnostic push)
  #define DISABLE_WARNING_POP _Pragma(GCC diagnostic pop)
  #define DISABLE_WARNING(name) _Pragma(GCC diagnostic ignored #name)
  #define DISABLE_UNREACHABLE_CODE
#endif

#define POINTER_TO_IMPLEMENTATION_IDIOM                                                            \
  struct Impl;                                                                                     \
  std::unique_ptr<Impl> m_pimpl;

#endif // GRAPHICENGINE3D_GE_CONFIG_HPP
