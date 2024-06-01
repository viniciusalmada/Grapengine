#include "drawables/ge_drawing_object.hpp"

#include "profiling/ge_profiler.hpp"

using namespace GE;

DrawingObject::DrawingObject()
{
  m_vao = VertexArray::Make();
  m_vao->Bind();

  m_vbo = VertexBuffer::Make(nullptr, 0, m_vao->GetID());
  m_ibo = IndexBuffer::Make({}, m_vao->GetID());

  m_vao->SetVertexBuffer(m_vbo, VerticesData::GetLayout());
  m_vao->SetIndexBuffer(m_ibo);
}

void DrawingObject::UpdateVerticesData(const Ptr<VerticesData>& data)
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

void DrawingObject::SetVerticesData(const Ptr<VerticesData>& data)
{
  UpdateVerticesData(data);
}

void DrawingObject::SetIndicesData(const std::vector<u32>& indices)
{
  GE_PROFILE;
  m_vao->Bind();
  m_ibo->UpdateData(indices);
  m_triangles_count = indices.size() / 3UL;
}
