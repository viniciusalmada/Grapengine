#include "ge_draw_primitive.hpp"

#include "ge_data_types.hpp"
#include "ge_index_buffer.hpp"
#include "ge_renderer.hpp"
#include "ge_vertex_array.hpp"
#include "ge_vertex_buffer.hpp"

struct DrawPrimitive::Impl
{
  Ref<VertexArray> vao = nullptr;
  Ref<VertexBuffer> vbo = nullptr;
  Ref<IndexBuffer> ibo = nullptr;
  u64 triangles_count = 0;
};

DrawPrimitive::DrawPrimitive(const Ref<std::vector<SimpleVertexData>>& vertices,
                             const Ref<std::vector<u32>>& indices) :
    m_pimpl(MakeScope<Impl>())
{
  m_pimpl->vao = MakeRef<VertexArray>();
  m_pimpl->triangles_count = indices->size() / 3ul;
  m_pimpl->vao->Bind();

  u32 vertices_count = static_cast<u32>(vertices->size());

  float* v_data = reinterpret_cast<float*>(vertices->data());

  m_pimpl->vbo =
    MakeRef<VertexBuffer>(v_data, sizeof(SimpleVertexData) * vertices_count, m_pimpl->vao->GetID());
  m_pimpl->ibo =
    MakeRef<IndexBuffer>(indices->data(), static_cast<u32>(indices->size()), m_pimpl->vao->GetID());

  m_pimpl->vao->SetVertexBuffer(m_pimpl->vbo);
  m_pimpl->vao->SetIndexBuffer(m_pimpl->ibo);
}

void DrawPrimitive::Draw() const
{
  Renderer::DrawIndexed(m_pimpl->vao, static_cast<i32>(m_pimpl->triangles_count * 3));
}

DrawPrimitive::~DrawPrimitive() = default;
