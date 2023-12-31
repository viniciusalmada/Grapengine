#include "ge_vertex_buffer.hpp"

#include <ge_gl_checkers.hpp>
#include <glad/glad.h>

struct VertexBuffer::Impl
{
  u32 id = 0;
  u32 parent = 0;
};

VertexBuffer::VertexBuffer(const void* ptr, u64 verticesSize, u32 parent) :
    m_pimpl(MakeScope<Impl>())
{
  Assert(GL::IsVAOBound(parent), "The associated VAO lacks a binding");

  m_pimpl->parent = parent;

  glGenBuffers(1, &m_pimpl->id);
  glBindBuffer(GL_ARRAY_BUFFER, m_pimpl->id);
  glBufferData(GL_ARRAY_BUFFER, verticesSize, ptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer() = default;

void VertexBuffer::Bind() const
{
  Assert(GL::IsVAOBound(m_pimpl->parent), "The associated VAO lacks a binding");

  glBindBuffer(GL_ARRAY_BUFFER, m_pimpl->id);
}

void VertexBuffer::UpdateData(const void* data, u64 size)
{
  Bind();
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}