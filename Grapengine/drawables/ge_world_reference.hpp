#ifndef GRAPENGINE_GE_WORLD_REFERENCE_HPP
#define GRAPENGINE_GE_WORLD_REFERENCE_HPP

#include "core/ge_type_aliases.hpp"
#include "drawables/ge_cube.hpp"
#include "drawables/ge_drawing_object.hpp"
#include "ge_cylinder.hpp"
#include "math/ge_vector.hpp"
#include "renderer/ge_vertex_array.hpp"

namespace GE
{
  class IShaderProgram;

  class WorldReference
  {
  public:
    WorldReference(const Ptr<IShaderProgram>& shader, u64 platformSize);
    ~WorldReference();

    void DrawBatch() const;

    void ShowPlatform(bool show);

    [[nodiscard]] Ptr<DrawingObject> GetVAO() const;
    [[nodiscard]] Mat4 GetModelMatrix() const;

  private:
    Ptr<IShaderProgram> m_shader;
    Ptr<Texture2D> m_blank_texture;
    Ptr<Cube> m_platform;
    Ptr<Cylinder> m_x_axis;
    Ptr<Cylinder> m_y_axis;
    Ptr<Cylinder> m_z_axis;
    bool m_show_platform = true;
    u64 m_platform_side_size;
  };
}

#endif // GRAPENGINE_GE_WORLD_REFERENCE_HPP
