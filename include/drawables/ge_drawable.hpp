#ifndef GRAPHICENGINE3D_GE_DRAWABLE_HPP
#define GRAPHICENGINE3D_GE_DRAWABLE_HPP

#include "renderer/ge_index_buffer.hpp"
#include "renderer/ge_vertex_array.hpp"
#include "renderer/ge_vertex_buffer.hpp"

class Drawable
{
public:
  virtual ~Drawable() = default;

  virtual void Draw() const = 0;
};

#endif // GRAPHICENGINE3D_GE_DRAWABLE_HPP
