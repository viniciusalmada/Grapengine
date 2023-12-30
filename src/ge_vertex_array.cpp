#include "ge_vertex_array.hpp"

#include "ge_index_buffer.hpp"
#include "ge_vertex_buffer.hpp"

#include <ge_gl_checkers.hpp>
#include <glad/glad.h>

namespace
{
  int GetComponentCount(const BufferElem& e)
  {
    switch (e.type)
    {
    case ShaderDataType::Float:
    case ShaderDataType::Int:
    case ShaderDataType::Bool:
      return 1;
    case ShaderDataType::Float2:
    case ShaderDataType::Int2:
      return 2;
    case ShaderDataType::Float3:
    case ShaderDataType::Int3:
      return 3;
    case ShaderDataType::Float4:
    case ShaderDataType::Int4:
      return 4;
    case ShaderDataType::Mat3:
      return 3 * 3;
    case ShaderDataType::Mat4:
      return 4 * 4;
    case ShaderDataType::None:
      return 0;
    }

    return 0;
  }

  unsigned int ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
  {
    switch (type)
    {
    case ShaderDataType::Float:
    case ShaderDataType::Float2:
    case ShaderDataType::Float3:
    case ShaderDataType::Float4:
    case ShaderDataType::Mat3:
    case ShaderDataType::Mat4:
      return GL_FLOAT;
    case ShaderDataType::Int:
    case ShaderDataType::Int2:
    case ShaderDataType::Int3:
    case ShaderDataType::Int4:
      return GL_INT;
    case ShaderDataType::Bool:
      return GL_BOOL;
    case ShaderDataType::None:
      return 0;
    }

    return 0;
  }
}

VertexArray::VertexArray() : id(0), vertex_buffer(nullptr), index_buffer(nullptr)
{
  glCreateVertexArrays(1, &id);
}

VertexArray::~VertexArray()
{
  glDeleteVertexArrays(1, &id);
}

void VertexArray::Bind() const
{
  glBindVertexArray(id);
  if (vertex_buffer)
    vertex_buffer->Bind();
  if (index_buffer)
    index_buffer->Bind();
}

void VertexArray::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
  if (!GL::CheckValidVAO(id))
    return;

  const auto& layout = vertexBuffer->GetLayout();

  unsigned int attrib_index = 0;
  for (const auto& elem : layout.elements)
  {
    glEnableVertexAttribArray(attrib_index);
    std::size_t offset = elem.offset;
    glVertexAttribPointer(attrib_index,
                          GetComponentCount(elem),
                          ShaderDataTypeToOpenGLBaseType(elem.type),
                          elem.normalized,
                          layout.stride,
                          (void*)offset);
    attrib_index++;
  }
  this->vertex_buffer = vertexBuffer;
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
  this->index_buffer = indexBuffer;
}