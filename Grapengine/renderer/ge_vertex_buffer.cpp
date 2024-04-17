#include "renderer/ge_vertex_buffer.hpp"

#include "core/ge_assert.hpp"
#include "renderer/ge_gl_checkers.hpp"

#include <glad/glad.h>

using namespace GE;

VertexBuffer::VertexBuffer(const void* ptr, u64 verticesSize, u32 parent)
{
  GE::Assert(IsVAOBound(parent), "The associated VAO lacks a binding");

  m_parent = parent;

  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
  glBufferData(GL_ARRAY_BUFFER, i64(verticesSize), ptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer() = default;

void VertexBuffer::Bind() const
{
  GE::Assert(IsVAOBound(m_parent), "The associated VAO lacks a binding");

  glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::UpdateData(const void* data, u64 size) const
{
  Bind();
  glBufferSubData(GL_ARRAY_BUFFER, 0, i64(size), data);
}
