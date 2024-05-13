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
    Mesh(std::string_view path, const Ref<IShaderProgram>& shader);

    ~Mesh() override;
    void Draw() const override;

  private:
    Color m_color = Colors::MAGENTA;
    Ref<DrawingObject> m_draw_primitive;
    Ref<Cube> m_bbox;
    Ref<IShaderProgram> m_shader;
    Ref<Texture2D> m_texture;
    std::vector<Vec3> m_vertices;
    std::vector<Face> m_faces;
    std::vector<Ref<Cylinder>> m_normals;
  };
}

#endif // GRAPENGINE_GE_MESH_HPP
