#include "renderer/ge_index_buffer.hpp"

#include "core/ge_assert.hpp"
#include "renderer/ge_gl_checkers.hpp"

#include <glad/glad.h>

using namespace GE;

IndexBuffer::IndexBuffer(const u32* indices, u32 count, RendererID parent) :
    m_id(0), m_parent(parent)
{

  GE_ASSERT(IsVAOBound(u32(parent)), "The associated VAO lacks a binding")

  u32 id = 0;
  glGenBuffers(1, &id);
  m_id = RendererID{ id };
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, u32(count * sizeof(u32)), indices, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const
{
  GE_ASSERT(IsVAOBound(u32(m_parent)), "The associated VAO lacks a binding")

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, u32(m_id));
}
