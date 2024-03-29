#ifndef GRAPENGINE_VERTEXARRAY_HPP
#define GRAPENGINE_VERTEXARRAY_HPP
namespace GE
{
  class VertexBuffer;
  class IndexBuffer;
  class BufferLayout;

  class VertexArray
  {
  public:
    GE3D VertexArray();
    GE3D ~VertexArray();

    [[nodiscard]] GE3D bool IsValid() const;
    void Bind() const;
    GE3D void Unbind() const;

    void SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, Ref<BufferLayout> layout);
    void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

    [[nodiscard]] u32 GetID() const { return id; }

  private:
    u32 id;
    Ref<VertexBuffer> vertex_buffer;
    Ref<IndexBuffer> index_buffer;
  };
}

#endif // GRAPENGINE_VERTEXARRAY_HPP
