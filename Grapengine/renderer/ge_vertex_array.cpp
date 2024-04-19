#include "renderer/ge_vertex_array.hpp"

#include "core/ge_assert.hpp"
#include "renderer/ge_buffer_layout.hpp"
#include "renderer/ge_gl_checkers.hpp"
#include "renderer/ge_index_buffer.hpp"
#include "renderer/ge_vertex_buffer.hpp"

#include <glad/glad.h>

using namespace GE;

namespace
{
  i32 GetComponentCount(const BufferElem& e)
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

  u32 ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
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

void VertexArray::SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer,
                                  Ref<const BufferLayout> layout)
{
  GE_ASSERT(IsVAOBound(id), "The associated VAO lacks a binding")

  u32 attrib_index = 0;
  layout->ForEachElement(
    [&](auto&& elem)
    {
      glEnableVertexAttribArray(attrib_index);
      std::size_t offset = elem.offset;
      glVertexAttribPointer(attrib_index,
                            GetComponentCount(elem),
                            ShaderDataTypeToOpenGLBaseType(elem.type),
                            elem.normalized,
                            static_cast<i32>(layout->GetStride()),
                            reinterpret_cast<void*>(offset));
      attrib_index++;
    });
  this->vertex_buffer = vertexBuffer;
}

void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
  this->index_buffer = indexBuffer;
}

bool VertexArray::IsValid() const
{
  return bool(glIsVertexArray(this->id));
}

void VertexArray::Unbind() const
{
  if (IsVAOBound(id))
    glBindVertexArray(0);
}
