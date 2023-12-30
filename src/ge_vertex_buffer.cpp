#include "ge_vertex_buffer.hpp"

#include <ge_buffer_layout.hpp>
#include <ge_gl_checkers.hpp>
#include <glad/glad.h>

VertexBuffer::VertexBuffer(float* ptr, u64 verticesSize, u32 parent)
{
  Assert(GL::CheckValidVAO(parent), "The associated VAO lacks a binding");

  {
    layout = BufferLayout{};
    layout.elements = std::vector<BufferElem>{
      BufferElem{ "in_position", ShaderDataType::Float3, sizeof(float) * 3, 0, false },
      BufferElem{ "in_color", ShaderDataType::Float4, sizeof(float) * 4, sizeof(float) * 3, false }
    };

    u32 offset = 0;
    layout.stride = 0;

    for (auto& elem : layout.elements)
    {
      elem.offset = offset;
      offset += elem.size;
      layout.stride += elem.size;
    }
  }

  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, verticesSize, ptr, GL_DYNAMIC_DRAW);
}

void VertexBuffer::Bind() const
{
  Assert(GL::CheckValidVAO(parent), "The associated VAO lacks a binding");

  glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::UpdateData(const void* data, u32 size)
{
  Bind();
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
