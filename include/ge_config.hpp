#ifndef GRAPHICENGINE3D_GE_CONFIG_HPP
#define GRAPHICENGINE3D_GE_CONFIG_HPP

#if defined(GraphicEngine3D_EXPORTS)
  #define GE3D __declspec(dllexport)
#else
  #define GE3D __declspec(dllimport)
#endif

#endif // GRAPHICENGINE3D_GE_CONFIG_HPP
