#include "ge_entities.hpp"
#include "glad/glad.h"

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
  }

  bool CheckValidVAO(unsigned int vaoID)
  {
    // Check valid parent VAO
    bool is_valid_vao = glIsVertexArray(vaoID);
    if (!is_valid_vao)
      return false;

    // Check passed VAO is bound
    uint32_t current_VAO = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (int*)(&current_VAO));

    bool is_any_vao_bound = current_VAO != 0;
    if (!is_any_vao_bound)
      return false;

    bool is_vao_bound = current_VAO == vaoID;
    if (!is_vao_bound)
      return false;

    return true;
  }
}

VertexArray::VertexArray() : id(0), vertex_buffer(nullptr), index_buffer(nullptr)
{
  glGenVertexArrays(1, &id);
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
                          (int)elem.size,
                          (void*)offset);
    attrib_index++;
  }
  this->vertex_buffer = vertexBuffer;
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
  this->index_buffer = indexBuffer;
}

VertexBuffer::VertexBuffer(uint32_t verticesSize, unsigned int parent) :
    id(0),
    parent(parent),
    layout({
        {"in_position", ShaderDataType::Float3, sizeof(float) * 3,                 0, false},
        {   "in_color", ShaderDataType::Float4, sizeof(float) * 4, sizeof(float) * 3, false}
})
{
  if (!CheckValidVAO(parent))
    return;

  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, verticesSize, nullptr, GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Bind() const
{
  if (!CheckValidVAO(parent))
    return;

  glBindBuffer(GL_ARRAY_BUFFER, id);
}

void IndexBuffer::Bind() const
{
  if (!CheckValidVAO(parent))
    return;

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(const std::vector<uint32_t>& indices,
                                                 unsigned int parent)
{
  return std::make_shared<IndexBuffer>(indices, parent);
}

IndexBuffer::IndexBuffer(const std::vector<uint32_t>& indices, unsigned int parent) :
    id(0),
    count(indices.size()),
    parent(parent)
{
  if (!CheckValidVAO(parent))
    return;

  glGenBuffers(1, &id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               (long long)(count * sizeof(uint32_t)),
               indices.data(),
               GL_STATIC_DRAW);
}
