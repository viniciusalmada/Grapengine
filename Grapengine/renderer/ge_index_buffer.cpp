#include "renderer/ge_index_buffer.hpp"

#include "core/ge_assert.hpp"
#include "profiling/ge_profiler.hpp"
#include "renderer/ge_gl_checkers.hpp"

#include <glad/glad.h>

using namespace GE;

IndexBuffer::IndexBuffer(const std::vector<u32>& indices, u32 count, RendererID parent) :
    m_id(0), m_parent(parent)
{
  GE_PROFILE;
  GE_ASSERT(IsVAOBound(u32(parent)), "The associated VAO lacks a binding")

  u32 id = 0;
  glGenBuffers(1, &id);
  m_id = RendererID{ id };
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, u32(count * sizeof(u32)), indices.data(), GL_DYNAMIC_DRAW);
}

void IndexBuffer::Bind() const
{
  GE_PROFILE;
  GE_ASSERT(IsVAOBound(u32(m_parent)), "The associated VAO lacks a binding")

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, u32(m_id));
}

Ptr<IndexBuffer> IndexBuffer::Make(const std::vector<u32>& indices, RendererID parent)
{
  return MakeRef<IndexBuffer>(indices, indices.size(), parent);
}

void IndexBuffer::UpdateData(const std::vector<u32>& indices)
{
  GE_PROFILE;
  Bind();
  i32 curr_size = 0;
  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &curr_size);
  const auto size = indices.size() * sizeof(u32);
  if (size > u32(curr_size))
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<i64>(size), indices.data(), GL_DYNAMIC_DRAW);
  else
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
                    0,
                    static_cast<i64>(indices.size() * sizeof(u32)),
                    indices.data());
}
