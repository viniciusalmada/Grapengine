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
    static void Initialize(Ptr<Window> window);
    static void Shutdown();

    [[nodiscard]] static bool IsKeyPressed(KeyCode keyCode);
    [[nodiscard]] static bool IsMouseButtonPressed(KeyCode keyCode);
    [[nodiscard]] static Vec2 GetMouseXY();

  private:
    static Input& Get();

    Ptr<Window> m_windows;
  };
}

#endif // GRAPENGINE_GE_INPUT_HPP
