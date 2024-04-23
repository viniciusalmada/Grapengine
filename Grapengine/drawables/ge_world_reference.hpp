#ifndef GRAPENGINE_GE_WORLD_REFERENCE_HPP
#define GRAPENGINE_GE_WORLD_REFERENCE_HPP

#include "core/ge_macros.hpp"
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
    WorldReference(const Ref<IShaderProgram>& shader, u64 platformSize);
    ~WorldReference();

    void DrawBatch() const;

    void ShowPlatform(bool show);

    [[nodiscard]] Ref<DrawingObject> GetVAO() const;
    [[nodiscard]] Mat4 GetModelMatrix() const;

  private:
    Ref<IShaderProgram> m_shader;
    Ref<Texture2D> m_blank_texture;
    Ref<Cube> m_platform;
    Ref<Cylinder> m_x_axis;
    Ref<Cylinder> m_y_axis;
    Ref<Cylinder> m_z_axis;
    bool m_show_platform = true;
    u64 m_platform_side_size;
  };
}

#endif // GRAPENGINE_GE_WORLD_REFERENCE_HPP
