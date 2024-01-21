#ifndef GRAPENGINE_SHADERS_LIBRARY_HPP
#define GRAPENGINE_SHADERS_LIBRARY_HPP

#include <math/ge_vector.hpp>
#include <utils/ge_ipubsub.hpp>
namespace GE
{
  class IShaderProgram;
  class BufferLayout;

  enum class Shaders
  {
    POSITION_AND_TEXTURE2D,
  };

  class ShadersLibrary
  {
  public:
    GE3D static ShadersLibrary& Get();

    ShadersLibrary(const ShadersLibrary&) = delete;
    ShadersLibrary operator=(const ShadersLibrary&) = delete;

    [[nodiscard]] GE3D Ref<IShaderProgram> GetShader(Shaders) const;

    [[nodiscard]] GE3D Ref<BufferLayout> GetLayout(Shaders) const;

    void Activate(Shaders shader);

  private:
    ShadersLibrary();

    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}
#endif // GRAPENGINE_SHADERS_LIBRARY_HPP
