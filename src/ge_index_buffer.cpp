#include "renderer/ge_index_buffer.hpp"

#include "core/ge_assert.hpp"
#include "renderer/ge_gl_checkers.hpp"

#include <glad/glad.h>

using namespace GE;

struct IndexBuffer::Impl
{
  u32 id;
  u32 count;
  u32 parent;
};

IndexBuffer::IndexBuffer(const u32* indices, u32 count, u32 parent) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->id = 0;
  m_pimpl->count = count;
  m_pimpl->parent = parent;
  Assert(IsVAOBound(parent), "The associated VAO lacks a binding");

  glGenBuffers(1, &m_pimpl->id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pimpl->id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, (u32)(count * sizeof(u32)), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() = default;

void IndexBuffer::Bind() const
{
  Assert(IsVAOBound(m_pimpl->parent), "The associated VAO lacks a binding");

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pimpl->id);
}
