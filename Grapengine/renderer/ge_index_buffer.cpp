#include "renderer/ge_index_buffer.hpp"

#include "core/ge_assert.hpp"
#include "renderer/ge_gl_checkers.hpp"

#include <glad/glad.h>

using namespace GE;

IndexBuffer::IndexBuffer(const u32* indices, u32 count, u32 parent)
{
  m_id = 0;
  m_count = count;
  m_parent = parent;
  GE_ASSERT(IsVAOBound(parent), "The associated VAO lacks a binding")

  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, u32(count * sizeof(u32)), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() = default;

void IndexBuffer::Bind() const
{
  GE_ASSERT(IsVAOBound(m_parent), "The associated VAO lacks a binding")

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}
