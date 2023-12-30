#include "ge_index_buffer.hpp"

#include "ge_gl_checkers.hpp"

#include <glad/glad.h>

void IndexBuffer::Bind() const
{
  Assert(GL::CheckValidVAO(parent), "The associated VAO lacks a binding");

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

IndexBuffer::IndexBuffer(const u32* indices, u32 count, u32 parent) :
    id(0), count(count), parent(parent)
{
  Assert(GL::CheckValidVAO(parent), "The associated VAO lacks a binding");

  glGenBuffers(1, &id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, (u32)(count * sizeof(u32)), indices, GL_STATIC_DRAW);
}
