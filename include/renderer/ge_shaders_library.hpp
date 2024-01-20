#ifndef GRAPHIC_ENGINE3D_GE_SHADERS_LIBRARY_HPP
#define GRAPHIC_ENGINE3D_GE_SHADERS_LIBRARY_HPP

#include <math/ge_vector.hpp>
#include <utils/ge_ipubsub.hpp>

class IShaderProgram;

enum class Shaders
{
  POSITION_AND_TEXTURE2D,
};

class ShadersLibrary
{
public:
  GE3D static ShadersLibrary& Get();

  void SubToCameraPub(IPublisher<Mat4>& pub) const;

  ShadersLibrary(const ShadersLibrary&) = delete;
  ShadersLibrary operator=(const ShadersLibrary&) = delete;

  [[nodiscard]] GE3D Ref<IShaderProgram> GetShader(Shaders) const;

  void Activate(Shaders shader);

private:
  ShadersLibrary();

  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHIC_ENGINE3D_GE_SHADERS_LIBRARY_HPP
