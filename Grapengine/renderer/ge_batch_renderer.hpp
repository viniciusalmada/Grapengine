#ifndef GRAPENGINE_GE_BATCH_RENDERER_HPP
#define GRAPENGINE_GE_BATCH_RENDERER_HPP

#include "drawables/ge_drawing_object.hpp"
#include "renderer/ge_vertices_data.hpp"
#include "renderer/shader_programs/ge_material_shader.hpp"

namespace GE
{
  class BatchRenderer
  {
  public:
    explicit BatchRenderer();

    void SetAmbientLight(const Color& color, f32 str);
    void SetLightsSources(const std::vector<std::tuple<Vec3, Color, f32>>& props);

    void Begin(const Mat4& cameraMatrix);

    void End();

    void PushObject(VerticesData&& vd, const std::vector<u32>& indices, const Mat4& modelMat);

  private:
    void Draw() const;

    Ptr<MaterialShader> m_shader;
    DrawingObject m_drawing_object;
    std::pair<Ptr<VerticesData>, std::vector<u32>> m_vertices_data;
  };
} // GE

#endif // GRAPENGINE_GE_BATCH_RENDERER_HPP
