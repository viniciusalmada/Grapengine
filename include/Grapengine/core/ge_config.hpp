#ifndef GRAPENGINE_CONFIG_HPP
#define GRAPENGINE_CONFIG_HPP

#if defined(GRAPENGINE_EXPORTS)
  #define GE3D __declspec(dllexport)
#else
  #define GE3D __declspec(dllimport)
#endif

#endif // GRAPENGINE_CONFIG_HPP
