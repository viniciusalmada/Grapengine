#ifndef GRAPENGINE_VERTEX_BUFFER_HPP
#define GRAPENGINE_VERTEX_BUFFER_HPP
namespace GE
{
  class VertexBuffer
  {
  public:
    VertexBuffer(const void* ptr, u64 verticesSize, u32 parent);
    ~VertexBuffer();

    void Bind() const;

    void UpdateData(const void* data, u64 size) const;

  private:
    u32 m_id = 0;
    u32 m_parent = 0;
  };
}

#endif // GRAPENGINE_VERTEX_BUFFER_HPP
