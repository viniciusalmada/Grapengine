#ifndef GRAPHICENGINE3D_GE_ENTITIES_HPP
#define GRAPHICENGINE3D_GE_ENTITIES_HPP

#include "ge_vector.hpp"

#include <memory>
#include <string>
#include <vector>

struct SimpleVertexData
{
  Vec3 position;
  Vec4 color;
};

enum class ShaderDataType
{
  None,
  Float,
  Float2,
  Float3,
  Float4,
  Mat3,
  Mat4,
  Int,
  Int2,
  Int3,
  Int4,
  Bool
};

struct BufferElem
{
  std::string name;
  ShaderDataType type;
  unsigned int size;
  unsigned int offset;
  bool normalized;
};

struct BufferLayout
{
  std::vector<BufferElem> elements;
  unsigned int stride;
};

class VertexBuffer
{
public:
  VertexBuffer(float* ptr, uint32_t verticesSize, unsigned int parent);

  [[nodiscard]] const BufferLayout& GetLayout() const { return layout; };

  void Bind() const;

  void UpdateData(const void* data, uint32_t size);

private:
  unsigned int id;
  unsigned int parent;
  BufferLayout layout;
};

class IndexBuffer
{
public:
  IndexBuffer(const uint32_t* indices,uint32_t count,  unsigned int parent);

  void Bind() const;

private:
  unsigned int id;
  unsigned int count;
  unsigned int parent;
};

class VertexArray
{
public:
  VertexArray();
  ~VertexArray();

  void Bind() const;

  void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
  void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

  [[nodiscard]] unsigned int GetID() const { return id; }

private:
  unsigned int id;
  std::shared_ptr<VertexBuffer> vertex_buffer;
  std::shared_ptr<IndexBuffer> index_buffer;
};

#endif // GRAPHICENGINE3D_GE_ENTITIES_HPP
