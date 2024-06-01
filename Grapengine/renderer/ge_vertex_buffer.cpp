#include "renderer/ge_vertex_buffer.hpp"

#include "core/ge_assert.hpp"
#include "renderer/ge_gl_checkers.hpp"

#include <glad/glad.h>

using namespace GE;

VertexBuffer::VertexBuffer(const void* ptr, u64 verticesSize, RendererID parent)
{
  GE_ASSERT(IsVAOBound(u32(parent)), "The associated VAO lacks a binding")

  m_parent = parent;

  u32 id = 0;
  glGenBuffers(1, &id);
  m_id = RendererID{ id };
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, i64(verticesSize), ptr, GL_DYNAMIC_DRAW);
}

void VertexBuffer::Bind() const
{
  GE_ASSERT(IsVAOBound(u32(m_parent)), "The associated VAO lacks a binding")

  glBindBuffer(GL_ARRAY_BUFFER, u32(m_id));
}

void VertexBuffer::UpdateData(const void* data, const u64 size) const
{
  Bind();
  // Get current size
  i32 curr_size = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &curr_size);
  if (size > u32(curr_size))
    glBufferData(GL_ARRAY_BUFFER, static_cast<i64>(size), data, GL_DYNAMIC_DRAW);
  else
    glBufferSubData(GL_ARRAY_BUFFER, 0, i64(size), data);
}

Ptr<VertexBuffer> VertexBuffer::Make(const void* ptr, u64 verticesSize, RendererID parent)
{
  return MakeRef<VertexBuffer>(ptr, verticesSize, parent);
}
