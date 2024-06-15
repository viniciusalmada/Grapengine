#ifndef GRAPENGINE_CYLINDER_HPP
#define GRAPENGINE_CYLINDER_HPP

#include "drawables/ge_color.hpp"
#include "drawables/ge_drawable.hpp"
#include "math/ge_vector.hpp"

namespace GE
{
  class Cylinder final : public Drawable
  {
  public:
    static Ptr<Cylinder>
    Make(const Vec3& basePoint, f32 radius, const Vec3& direction, f32 height, Color color);

    Cylinder(const Vec3& basePoint, f32 radius, const Vec3& direction, f32 height, Color color);
    ~Cylinder() override;

    [[nodiscard]] VerticesData GetVerticesData(Color color) const override;
    [[nodiscard]] const std::vector<u32>& GetIndicesData() const override;

  private:
    Color m_color{ 0 };
    VerticesData m_vertices;
    std::vector<u32> m_indices;
  };
}

#endif // GRAPENGINE_CYLINDER_HPP
