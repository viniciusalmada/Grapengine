#ifndef GRAPENGINE_DRAWABLE_HPP
#define GRAPENGINE_DRAWABLE_HPP

#include "drawables/ge_color.hpp"
#include "renderer/ge_vertices_data.hpp"

namespace GE
{
  class Drawable final
  {
  public:
    explicit Drawable(const VerticesData& vertices, const std::vector<u32>& indices);

    void UpdateColor(const Color&);
    [[nodiscard]] const VerticesData& GetVerticesData() const;
    [[nodiscard]] virtual const std::vector<u32>& GetIndicesData() const;

  private:
    VerticesData m_vertices_data;
    std::vector<u32> m_indices_data;
  };
}

#endif // GRAPENGINE_DRAWABLE_HPP
