#ifndef GRAPENGINE_DRAWABLE_HPP
#define GRAPENGINE_DRAWABLE_HPP

#include "renderer/ge_ishader_program.hpp"

namespace GE
{
  class Drawable
  {
  public:
    explicit Drawable(const Ref<IShaderProgram>& /*shader*/) {}

    virtual ~Drawable() = default;

    virtual void Draw() const = 0;
  };
}

#endif // GRAPENGINE_DRAWABLE_HPP
