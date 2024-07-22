#ifndef GRAPENGINE_GE_MESH_HPP
#define GRAPENGINE_GE_MESH_HPP

#include "drawables/ge_drawable.hpp"

namespace GE
{
  struct Face
  {
    IVec3 indices;
    Vec3 center;
    Vec3 normal;
  };

  class Mesh
  {
  public:
    Mesh(std::string_view path);

    const Drawable& GetDrawable() const;

  private:
    void UpdateVerticesData() const;

    Drawable m_drawable;
  };
}

#endif // GRAPENGINE_GE_MESH_HPP
