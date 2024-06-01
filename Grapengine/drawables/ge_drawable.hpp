#ifndef GRAPENGINE_DRAWABLE_HPP
#define GRAPENGINE_DRAWABLE_HPP

#include "renderer/ge_vertices_data.hpp"

namespace GE
{
  class Drawable
  {
  public:
    virtual ~Drawable();

    virtual VerticesData GetVerticesData() const = 0;
    virtual const std::vector<u32>& GetIndicesData() const = 0;
  };
}

#endif // GRAPENGINE_DRAWABLE_HPP
