#ifndef GRAPENGINE_GE_MESH_HPP
#define GRAPENGINE_GE_MESH_HPP

#include "drawables/ge_drawable.hpp"

namespace GE
{
  class Mesh : public Drawable
  {
  public:
    Mesh(std::string_view path);

    ~Mesh() override;

    [[nodiscard]] VerticesData GetVerticesData(Color color) const override;
    [[nodiscard]] const std::vector<u32>& GetIndicesData() const override;

  private:
    struct Face
    {
      IVec3 indices;
      Vec3 center;
      Vec3 normal;
    };

    [[nodiscard]] Vec3 GetNormal(u64 idx) const;
    void UpdateVerticesData() const;
    void ReadFile(std::string_view path);

    std::vector<Vec3> m_vertices;
    std::vector<Face> m_faces;
    std::vector<Vec3> m_normals;
    mutable Color m_color = Colors::MAGENTA;
    mutable VerticesData m_vertices_data;
    std::vector<u32> m_indices;
  };
}

#endif // GRAPENGINE_GE_MESH_HPP
