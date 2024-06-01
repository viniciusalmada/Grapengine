#ifndef GRAPENGINE_DRAWING_OBJECT_HPP
#define GRAPENGINE_DRAWING_OBJECT_HPP

#include "renderer/ge_index_buffer.hpp"
#include "renderer/ge_vertex_array.hpp"
#include "renderer/ge_vertex_buffer.hpp"
#include "renderer/ge_vertices_data.hpp"

namespace GE
{
  class DrawingObject
  {
  public:
    explicit DrawingObject();

    void SetVerticesData(const Ptr<VerticesData>& data);
    void SetIndicesData(const std::vector<u32>& indices);

    void UpdateVerticesData(const Ptr<VerticesData>& data);

    void Bind() const;

    [[nodiscard]] i32 IndicesCount() const;

  private:
    Ptr<VertexArray> m_vao = nullptr;
    Ptr<VertexBuffer> m_vbo = nullptr;
    Ptr<IndexBuffer> m_ibo = nullptr;
    u64 m_triangles_count = 0;
  };
}

#endif // GRAPENGINE_DRAWING_OBJECT_HPP
