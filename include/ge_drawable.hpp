#ifndef GRAPHICENGINE3D_GE_DRAWABLE_HPP
#define GRAPHICENGINE3D_GE_DRAWABLE_HPP

#include "ge_index_buffer.hpp"
#include "ge_vertex_array.hpp"
#include "ge_vertex_buffer.hpp"

class Drawable
{
public:
  virtual ~Drawable() = default;

  virtual void Draw() const = 0;
};

#endif // GRAPHICENGINE3D_GE_DRAWABLE_HPP
