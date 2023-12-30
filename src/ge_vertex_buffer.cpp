#include "ge_vertex_buffer.hpp"

#include <ge_buffer_layout.hpp>
#include <ge_gl_checkers.hpp>
#include <glad/glad.h>

struct VertexBuffer::Impl
{
  u32 id = 0;
  u32 parent = 0;
  BufferLayout layout;
};

VertexBuffer::VertexBuffer(float* ptr, u64 verticesSize, u32 parent) :
    m_pimpl(MakeScope<Impl>())
{
  Assert(GL::CheckValidVAO(parent), "The associated VAO lacks a binding");

  m_pimpl->parent = parent;

  {
    m_pimpl->layout = BufferLayout{};
    m_pimpl->layout.elements = std::vector<BufferElem>{
      BufferElem{ "in_position", ShaderDataType::Float3, sizeof(float) * 3, 0, false },
      BufferElem{ "in_color", ShaderDataType::Float4, sizeof(float) * 4, sizeof(float) * 3, false }
    };

    u32 offset = 0;
    m_pimpl->layout.stride = 0;

    for (auto& elem : m_pimpl->layout.elements)
    {
      elem.offset = offset;
      offset += elem.size;
      m_pimpl->layout.stride += elem.size;
    }
  }

  glGenBuffers(1, &m_pimpl->id);
  glBindBuffer(GL_ARRAY_BUFFER, m_pimpl->id);
  glBufferData(GL_ARRAY_BUFFER, verticesSize, ptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer() = default;

void VertexBuffer::Bind() const
{
  Assert(GL::CheckValidVAO(m_pimpl->parent), "The associated VAO lacks a binding");

  glBindBuffer(GL_ARRAY_BUFFER, m_pimpl->id);
}

void VertexBuffer::UpdateData(const void* data, u32 size)
{
  Bind();
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

const BufferLayout& VertexBuffer::GetLayout() const
{
  return m_pimpl->layout;
}
