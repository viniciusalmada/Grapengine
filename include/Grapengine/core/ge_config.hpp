#ifndef GRAPENGINE_CONFIG_HPP
#define GRAPENGINE_CONFIG_HPP

#if defined(GE_PLATFORM_WINDOWS) || defined(GE_PLATFORM_LINUX)
  #define GE3D
#else
  #error "Unsupported platform"
#endif

#endif // GRAPENGINE_CONFIG_HPP
