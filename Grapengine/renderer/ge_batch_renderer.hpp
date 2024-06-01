#ifndef GRAPENGINE_GE_BATCH_RENDERER_HPP
#define GRAPENGINE_GE_BATCH_RENDERER_HPP

#include "drawables/ge_drawing_object.hpp"
#include "renderer/ge_ishader_program.hpp"
#include "renderer/ge_vertices_data.hpp"

namespace GE
{
  class BatchRenderer
  {
  public:
    explicit BatchRenderer();

    void Begin();

    void End();

    void PushObject(Ptr<IShaderProgram> shader,
                    VerticesData&& vd,
                    const std::vector<u32>& indices,
                    const Mat4& modelMat);

  private:
    void Draw(const DrawingObject& drawingObject);

    //    std::set<Ptr<IShaderProgram>> m_shaders;
    std::map<Ptr<IShaderProgram>, DrawingObject> m_drawing_objects;
    std::map<Ptr<IShaderProgram>, std::pair<Ptr<VerticesData>, std::vector<u32>>> m_vertices_data;
  };
} // GE

#endif // GRAPENGINE_GE_BATCH_RENDERER_HPP
