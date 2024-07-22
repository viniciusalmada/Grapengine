#ifndef GRAPENGINE_CUBE_HPP
#define GRAPENGINE_CUBE_HPP

#include "ge_color.hpp"
#include "ge_drawable.hpp"
#include "ge_drawing_object.hpp"
#include "math/ge_vector.hpp"
#include "renderer/ge_ishader_program.hpp"
#include "renderer/ge_texture_2d.hpp"
#include "renderer/ge_vertex_array.hpp"

namespace GE
{
  class Cube final
  {
  public:
    Cube();

    const Drawable& GetDrawable() const;

  private:
    Ptr<Texture2D> m_texture;
    Drawable m_drawable;
  };
}

#endif // GRAPENGINE_CUBE_HPP
