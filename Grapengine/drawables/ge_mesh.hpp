#ifndef GRAPENGINE_GE_MESH_HPP
#define GRAPENGINE_GE_MESH_HPP

#include "core/ge_macros.hpp"
#include "ge_drawable.hpp"

namespace GE
{
  class Mesh : public Drawable
  {
  public:
    Mesh(std::string_view path, const Ref<IShaderProgram>& shader);

    ~Mesh() override;
    void Draw() const override;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_GE_MESH_HPP
