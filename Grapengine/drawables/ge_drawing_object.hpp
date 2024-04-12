#ifndef GRAPENGINE_DRAWING_OBJECT_HPP
#define GRAPENGINE_DRAWING_OBJECT_HPP

#include "renderer/ge_index_buffer.hpp"
#include "renderer/ge_vertex_array.hpp"
#include "renderer/ge_vertex_buffer.hpp"

namespace GE
{
  class VerticesData;

  class DrawingObject
  {
  public:
    DrawingObject(const Ref<VerticesData>& vertices, const Ref<std::vector<u32>>& indices);
    ~DrawingObject();

    [[deprecated]] void Draw() const;

    void UpdateVerticesData(const Ref<VerticesData>&);

    void Bind() const;

    i32 IndicesCount() const;

  private:
    Ref<VertexArray> m_vao = nullptr;
    Ref<VertexBuffer> m_vbo = nullptr;
    Ref<IndexBuffer> m_ibo = nullptr;
    u64 m_triangles_count = 0;
  };
}

#endif // GRAPENGINE_DRAWING_OBJECT_HPP
