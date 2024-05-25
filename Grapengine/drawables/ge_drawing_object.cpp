#include "drawables/ge_drawing_object.hpp"

#include "profiling/ge_profiler.hpp"
#include "renderer/ge_index_buffer.hpp"
#include "renderer/ge_renderer.hpp"
#include "renderer/ge_vertex_array.hpp"
#include "renderer/ge_vertex_buffer.hpp"
#include "renderer/ge_vertices_data.hpp"

using namespace GE;

DrawingObject::DrawingObject(const Ref<VerticesData>& vertices,
                             const Ref<std::vector<u32>>& indices) :
    m_triangles_count(indices->size() / 3UL)
{
  GE_PROFILE;
  m_vao = MakeRef<VertexArray>();

  m_vao->Bind();

  m_vbo = MakeRef<VertexBuffer>(vertices->GetPtr(), vertices->GetSize(), m_vao->GetID());
  m_ibo = MakeRef<IndexBuffer>(indices->data(), static_cast<u32>(indices->size()), m_vao->GetID());

  m_vao->SetVertexBuffer(m_vbo, vertices->GetLayout());
  m_vao->SetIndexBuffer(m_ibo);
}

DrawingObject::~DrawingObject() = default;

void DrawingObject::Draw() const
{
  GE_PROFILE;
  Renderer::DrawIndexed(m_vao, static_cast<i32>(m_triangles_count * 3));
}

void DrawingObject::UpdateVerticesData(const Ref<VerticesData>& data)
{
  GE_PROFILE;
  m_vao->Bind();
  m_vbo->UpdateData(data->GetPtr(), data->GetSize());
}

void GE::DrawingObject::Bind() const
{
  m_vao->Bind();
}

i32 GE::DrawingObject::IndicesCount() const
{
  return static_cast<i32>(m_triangles_count * 3);
}
