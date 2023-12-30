#ifndef GRAPHICENGINE3D_GE_INDEX_BUFFER_HPP
#define GRAPHICENGINE3D_GE_INDEX_BUFFER_HPP

class IndexBuffer
{
public:
  IndexBuffer(const u32* indices, u32 count, u32 parent);

  void Bind() const;

private:
  u32 id;
  u32 count;
  u32 parent;
};

#endif // GRAPHICENGINE3D_GE_INDEX_BUFFER_HPP
