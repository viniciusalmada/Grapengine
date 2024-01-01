#ifndef GRAPHIC_ENGINE3D_GE_SHADERS_LIBRARY_HPP
#define GRAPHIC_ENGINE3D_GE_SHADERS_LIBRARY_HPP

#include "ge_system.hpp"

class ShadersLibrary
{
public:
  static ShadersLibrary& Get();

  ShadersLibrary(const ShadersLibrary&) = delete;
  ShadersLibrary operator=(const ShadersLibrary&) = delete;

private:
  ShadersLibrary();

  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHIC_ENGINE3D_GE_SHADERS_LIBRARY_HPP
