#include "drawables/ge_draw_primitive.hpp"

#include "renderer/ge_index_buffer.hpp"
#include "renderer/ge_renderer.hpp"
#include "renderer/ge_vertex_array.hpp"
#include "renderer/ge_vertex_buffer.hpp"
#include "renderer/ge_vertices_data.hpp"

using namespace GE;

struct DrawPrimitive::Impl
{
  Ref<VertexArray> vao = nullptr;
  Ref<VertexBuffer> vbo = nullptr;
  Ref<IndexBuffer> ibo = nullptr;
  u64 triangles_count = 0;
};

DrawPrimitive::DrawPrimitive(const Ref<VerticesData>& vertices, const Ref<std::vector<u32>>& indices) :
    m_pimpl(MakeScope<Impl>())
{
  m_pimpl->vao = MakeRef<VertexArray>();
  m_pimpl->triangles_count = indices->size() / 3ul;
  m_pimpl->vao->Bind();

  m_pimpl->vbo =
    MakeRef<VertexBuffer>(vertices->GetPtr(), vertices->GetSize(), m_pimpl->vao->GetID());
  m_pimpl->ibo =
    MakeRef<IndexBuffer>(indices->data(), static_cast<u32>(indices->size()), m_pimpl->vao->GetID());

  m_pimpl->vao->SetVertexBuffer(m_pimpl->vbo, vertices->GetLayout());
  m_pimpl->vao->SetIndexBuffer(m_pimpl->ibo);
}

DrawPrimitive::~DrawPrimitive() = default;

void DrawPrimitive::Draw() const
{
  Renderer::DrawIndexed(m_pimpl->vao, static_cast<i32>(m_pimpl->triangles_count * 3));
}

void DrawPrimitive::UpdateVerticesData(const Ref<VerticesData>& data)
{
  m_pimpl->vao->Bind();
  m_pimpl->vbo->UpdateData(data->GetPtr(), data->GetSize());
}
