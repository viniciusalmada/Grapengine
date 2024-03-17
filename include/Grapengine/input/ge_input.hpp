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
    explicit Input(Ref<Window> window);
    ~Input();

    [[nodiscard]] static bool IsKeyPressed(KeyCode keyCode);
    [[nodiscard]] static bool IsMouseButtonPressed(KeyCode keyCode);
    [[nodiscard]] static Vec2 GetMouseXY();
  };
}

#endif // GRAPENGINE_GE_INPUT_HPP
