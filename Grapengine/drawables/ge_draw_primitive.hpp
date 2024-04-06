#ifndef GRAPENGINE_DRAW_PRIMITIVE_HPP
#define GRAPENGINE_DRAW_PRIMITIVE_HPP
namespace GE
{
  class VerticesData;

  class DrawPrimitive
  {
  public:
    DrawPrimitive(const Ref<VerticesData>& vertices, const Ref<std::vector<u32>>& indices);
    ~DrawPrimitive();

    void Draw() const;

    void UpdateVerticesData(const Ref<VerticesData>&);

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_DRAW_PRIMITIVE_HPP
