#ifndef GRAPHICENGINE3D_GE_INDEX_BUFFER_HPP
#define GRAPHICENGINE3D_GE_INDEX_BUFFER_HPP

class IndexBuffer
{
public:
  IndexBuffer(const uint32_t* indices, uint32_t count, unsigned int parent);

  void Bind() const;

private:
  unsigned int id;
  unsigned int count;
  unsigned int parent;
};

#endif // GRAPHICENGINE3D_GE_INDEX_BUFFER_HPP
