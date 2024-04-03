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
    static void Initialize(Ref<Window> window);
    static Input& Get();
    static void Shutdown();

    [[nodiscard]] bool IsKeyPressed(KeyCode keyCode);
    [[nodiscard]] bool IsMouseButtonPressed(KeyCode keyCode);
    [[nodiscard]] Vec2 GetMouseXY();

  private:
    explicit Input(Ref<Window> window);

    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_GE_INPUT_HPP
