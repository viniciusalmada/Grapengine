#ifndef GRAPENGINE_RENDERER_HPP
#define GRAPENGINE_RENDERER_HPP

#include "math/ge_vector.hpp"
#include "renderer/ge_ishader_program.hpp"
#include "renderer/ge_vertices_data.hpp"
#include "utils/ge_dimension.hpp"

namespace GE
{
  class VertexArray;
  class DrawingObject;

  class Renderer
  {
  public:
    static void Init();

    static void SetViewport(u32 x, u32 y, Dimension dim);

    static void SetWireframeRenderMode(bool enabled);

    static void SetClearColor(const Vec4& color);

    static void Clear();

    static void DrawIndexed(const Ptr<VertexArray>& vao, i32 count);

    static void DrawObject(const Ptr<DrawingObject>& primitive);

    class Batch
    {
    public:
      static void Begin();

      static void End();

      static void PushObject(Ptr<IShaderProgram> shader,
                             VerticesData&& vd,
                             const std::vector<u32>& indices,
                             const Mat4& modelMat);
    };
  };
}

#endif
