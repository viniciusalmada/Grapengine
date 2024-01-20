#ifndef GRAPENGINE_INDEX_BUFFER_HPP
#define GRAPENGINE_INDEX_BUFFER_HPP

class IndexBuffer
{
public:
  IndexBuffer(const u32* indices, u32 count, u32 parent);
  ~IndexBuffer();

  void Bind() const;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPENGINE_INDEX_BUFFER_HPP
