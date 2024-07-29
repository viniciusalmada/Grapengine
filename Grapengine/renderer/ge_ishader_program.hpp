#ifndef GRAPENGINE_ISHADER_PROGRAM_HPP
#define GRAPENGINE_ISHADER_PROGRAM_HPP

#include "math/ge_vector.hpp"

namespace GE
{
  struct VertexStruct
  {
    Vec3 position;
    Vec2 texture_coord;
    Vec4 color;
    Vec3 normal;

    bool operator==(const VertexStruct& other) const = default;
  };

  class IShaderProgram
  {
  public:
    virtual ~IShaderProgram();

    virtual void Activate() = 0;
    virtual void Deactivate() = 0;

    virtual void UpdateViewProjectionMatrix(const Mat4& viewProj, const Vec3& viewPosition) = 0;
    virtual void UpdateTexture(int id) = 0;
  };
}

#endif // GRAPENGINE_ISHADER_HPP
