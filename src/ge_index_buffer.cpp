#include "ge_index_buffer.hpp"

#include "ge_gl_checkers.hpp"

#include <glad/glad.h>

void IndexBuffer::Bind() const
{
  if (!GL::CheckValidVAO(parent))
    return;

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

IndexBuffer::IndexBuffer(const uint32_t* indices, uint32_t count, unsigned int parent) :
    id(0), count(count), parent(parent)
{
  if (!GL::CheckValidVAO(parent))
    return;

  glGenBuffers(1, &id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               (long long)(count * sizeof(uint32_t)),
               indices,
               GL_STATIC_DRAW);
}
