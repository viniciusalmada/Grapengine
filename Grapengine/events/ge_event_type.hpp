#ifndef GRAPENGINE_EVENT_TYPE_HPP
#define GRAPENGINE_EVENT_TYPE_HPP

#include "core/ge_type_aliases.hpp"
#include "input/ge_key_codes.hpp"

#include <variant>

namespace GE
{
  enum class EvType : u8
  {
    NONE,
    WINDOW_CLOSE,
    WINDOW_RESIZE,
    //  WINDOW_FOCUS,
    //  WINDOW_LOST_FOCUS,
    //  WINDOW_MOVED,
    //  APP_TICK,
    //  APP_UPDATE,
    //  APP_RENDER,
    KEY_PRESS,
    KEY_RELEASE,
    //  KEY_TYPED,
    MOUSE_BUTTON_PRESSED,
    MOUSE_BUTTON_RELEASE,
    MOUSE_MOVE,
    MOUSE_SCROLL
  };

  using WindowResizeData = std::pair<u32, u32>;
  using MousePairData = std::pair<f32, f32>;

  using EvData = std::variant<WindowResizeData, KeyCode, MousePairData, std::monostate>;

  template <typename... Ts>
  struct TypeGetter : Ts...
  {
    using Ts::operator()...;
  };

  template <typename... Ts>
  TypeGetter(Ts...) -> TypeGetter<Ts...>;
}
#endif
