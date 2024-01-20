#ifndef GRAPENGINE_EVENT_TYPE_HPP
#define GRAPENGINE_EVENT_TYPE_HPP

enum class EvType
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

using WindowCloseData = std::tuple<EvType>;
using WindowResizeData = std::tuple<EvType, i32, i32>;
using KeyPressData = std::tuple<EvType, i32>;
using KeyReleaseData = KeyPressData;
using MouseButtonPressData = KeyPressData;
using MouseButtonReleaseData = KeyPressData;
using MouseMoveData = std::tuple<EvType, float, float>;
using MouseScrollData = MouseMoveData;

using EvData = std::variant<WindowCloseData, WindowResizeData, KeyPressData, MouseMoveData>;

template <typename... Ts>
struct TypeGetter : Ts...
{
  using Ts::operator()...;
};

template <typename... Ts>
TypeGetter(Ts...) -> TypeGetter<Ts...>;

#endif
