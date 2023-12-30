#include "ge_vertex_buffer.hpp"

#include <ge_buffer_layout.hpp>
#include <ge_gl_checkers.hpp>
#include <glad/glad.h>

VertexBuffer::VertexBuffer(float* ptr, u32 verticesSize, u32 parent)
{
  if (!GL::CheckValidVAO(parent))
    return;

  {
    layout = BufferLayout{};
    layout.elements = std::vector<BufferElem>{
      BufferElem{ "in_position", ShaderDataType::Float3, sizeof(float) * 3, 0, false },
      BufferElem{ "in_texture",
                  ShaderDataType::Float2,
                  sizeof(float) * 2,
                  sizeof(float) * 3,
                  false }
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
  if (!GL::CheckValidVAO(parent))
    return;

  glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::UpdateData(const void* data, u32 size)
{
  Bind();
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
