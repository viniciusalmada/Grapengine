#ifndef GRAPENGINE_GE_INPUT_HPP
#define GRAPENGINE_GE_INPUT_HPP

#include "ge_key_codes.hpp"
#include "math/ge_vector.hpp"

namespace GE
{
  class Window;

  class Input
  {
  public:
    Input(Ref<Window> window);
    ~Input();

    [[nodiscard]] bool IsKeyPressed(KeyCode keyCode) const;
    [[nodiscard]] bool IsMouseButtonPressed(KeyCode keyCode) const;
    [[nodiscard]] Vec2 GetMouseXY() const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_GE_INPUT_HPP
