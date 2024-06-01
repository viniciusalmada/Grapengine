#ifndef GRAPENGINE_BUFFER_HANDLER_HPP
#define GRAPENGINE_BUFFER_HANDLER_HPP

#include "math/ge_vector.hpp"
#include "renderer/ge_vertices_data.hpp"

namespace GE
{
  class BufferHandler
  {
  public:
    static void UpdatePosition(VerticesData& vd, const Mat4& modelMatrix);
  };

} // GE

#endif // GRAPENGINE_BUFFER_HANDLER_HPP
