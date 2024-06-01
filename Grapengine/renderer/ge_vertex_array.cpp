#include "renderer/ge_vertex_array.hpp"

#include "core/ge_assert.hpp"
#include "core/ge_platform.hpp"
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
    switch (e.purpose)
    {
    case DataPurpose::POSITION_F3:
    case DataPurpose::NORMAL_F3:
      return 3;
    case DataPurpose::COLOR_F4:
      return 4;
    case DataPurpose::TEXTURE_COORDINATE_F2:
      return 2;
    }
    Platform::Unreachable();
  }

  u32 ShaderDataTypeToOpenGLBaseType(DataPurpose type)
  {
    switch (type)
    {
    case DataPurpose::POSITION_F3:
    case DataPurpose::COLOR_F4:
    case DataPurpose::TEXTURE_COORDINATE_F2:
    case DataPurpose::NORMAL_F3:
      return GL_FLOAT;
    }
    Platform::Unreachable();
  }
}

VertexArray::VertexArray() : id(0), vertex_buffer(nullptr), index_buffer(nullptr)
{
  u32 v_id = 0;
  glCreateVertexArrays(1, &v_id);
  id = RendererID{ v_id };
}

VertexArray::~VertexArray()
{
  const u32 v_id = u32(id);
  glDeleteVertexArrays(1, &v_id);
}

void VertexArray::Bind() const
{
  glBindVertexArray(u32(id));
  if (vertex_buffer)
    vertex_buffer->Bind();
  if (index_buffer)
    index_buffer->Bind();
}

void VertexArray::SetVertexBuffer(const Ptr<VertexBuffer>& vertexBuffer, BufferLayout layout)
{
  GE_ASSERT(IsVAOBound(u32(id)), "The associated VAO lacks a binding")

  u32 attrib_index = 0;
  layout.ForEachElement(
    [&](auto&& elem)
    {
      glEnableVertexAttribArray(attrib_index);
      const std::size_t offset = elem.offset;
      glVertexAttribPointer(
        attrib_index,
        GetComponentCount(elem),
        ShaderDataTypeToOpenGLBaseType(elem.purpose),
        elem.normalized,
        static_cast<i32>(layout.GetStride()),
        reinterpret_cast<void*>(offset)); // NOLINT(*-pro-type-reinterpret-cast, *-no-int-to-ptr)
      attrib_index++;
    });
  this->vertex_buffer = vertexBuffer;
}

void VertexArray::SetIndexBuffer(const Ptr<IndexBuffer>& indexBuffer)
{
  this->index_buffer = indexBuffer;
}

bool VertexArray::IsValid() const
{
  return bool(glIsVertexArray(u32(id)));
}

void VertexArray::Unbind() const
{
  if (IsVAOBound(u32(id)))
    glBindVertexArray(0);
}

Ptr<VertexArray> VertexArray::Make()
{
  return MakeRef<VertexArray>();
}
