#ifndef GRAPENGINE_INDEX_BUFFER_HPP
#define GRAPENGINE_INDEX_BUFFER_HPP
namespace GE
{
  class IndexBuffer
  {
  public:
    IndexBuffer(const u32* indices, u32 count, u32 parent);
    ~IndexBuffer();

    void Bind() const;

  private:
    u32 m_id;
    u32 m_count;
    u32 m_parent;
  };
}
#endif // GRAPENGINE_INDEX_BUFFER_HPP
