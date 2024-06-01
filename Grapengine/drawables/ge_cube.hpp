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
  class Cube final : public Drawable
  {
  public:
    Cube(Color color);

    [[nodiscard]] VerticesData GetVerticesData() const override;
    [[nodiscard]] const std::vector<u32>& GetIndicesData() const override;

  private:
    Color m_color;
    Ptr<Texture2D> m_texture;
  };
}

#endif // GRAPENGINE_CUBE_HPP
