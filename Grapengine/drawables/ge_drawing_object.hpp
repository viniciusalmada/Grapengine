#ifndef GRAPENGINE_DRAWING_OBJECT_HPP
#define GRAPENGINE_DRAWING_OBJECT_HPP
namespace GE
{
  class VerticesData;

  class DrawingObject
  {
  public:
    DrawingObject(const Ref<VerticesData>& vertices, const Ref<std::vector<u32>>& indices);
    ~DrawingObject();

    [[deprecated]] void Draw() const;

    void UpdateVerticesData(const Ref<VerticesData>&);

    void Bind() const;

    i32 IndicesCount() const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_DRAWING_OBJECT_HPP
