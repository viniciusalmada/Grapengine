#ifndef GRAPENGINE_GE_MESH_HPP
#define GRAPENGINE_GE_MESH_HPP

#include "drawables/ge_cube.hpp"
#include "drawables/ge_cylinder.hpp"
#include "drawables/ge_drawable.hpp"

namespace GE
{
  struct Face
  {
    IVec3 indices;
    Vec3 center;
    Vec3 normal;
  };

  class Mesh : public Drawable
  {
  public:
    Mesh(std::string_view path);

    ~Mesh() override;

    VerticesData GetVerticesData(Color color) const override;
    const std::vector<u32>& GetIndicesData() const override;

  private:
    Color m_color = Colors::MAGENTA;
    VerticesData m_vertices_data;
    std::vector<u32> m_indices;
  };
}

#endif // GRAPENGINE_GE_MESH_HPP
