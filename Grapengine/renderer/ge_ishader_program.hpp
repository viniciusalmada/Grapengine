#ifndef GRAPENGINE_ISHADER_PROGRAM_HPP
#define GRAPENGINE_ISHADER_PROGRAM_HPP

#include <math/ge_vector.hpp>

namespace GE
{
  class BufferLayout;

  class IShaderProgram
  {
  public:
    virtual ~IShaderProgram();

    virtual void Activate() = 0;
    virtual void Deactivate() = 0;

    virtual void UpdateModelMatrix(Mat4 model) = 0;
    virtual void UpdateViewProjectionMatrix(Mat4 viewProj) = 0;
    virtual void UpdateTexture(int id) = 0;

    [[nodiscard]] virtual Ptr<const BufferLayout> GetLayout() const = 0;
  };
}

#endif // GRAPENGINE_ISHADER_HPP
