#ifndef GRAPHICENGINE3D_GE_INDEX_BUFFER_HPP
#define GRAPHICENGINE3D_GE_INDEX_BUFFER_HPP

class IndexBuffer
{
public:
  IndexBuffer(const u32* indices, u32 count, u32 parent);
  ~IndexBuffer();

  void Bind() const;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHICENGINE3D_GE_INDEX_BUFFER_HPP
