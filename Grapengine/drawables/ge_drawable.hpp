#ifndef GRAPENGINE_DRAWABLE_HPP
#define GRAPENGINE_DRAWABLE_HPP

#include "drawables/ge_color.hpp"
#include "renderer/ge_vertices_data.hpp"

namespace GE
{
  class Drawable
  {
  public:
    virtual ~Drawable();

    [[nodiscard]] virtual VerticesData GetVerticesData(Color color) const = 0;
    [[nodiscard]] virtual const std::vector<u32>& GetIndicesData() const = 0;
  };
}

#endif // GRAPENGINE_DRAWABLE_HPP
