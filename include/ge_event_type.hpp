#ifndef GRAPHICENGINE3D_GE_EVENT_TYPE_HPP
#define GRAPHICENGINE3D_GE_EVENT_TYPE_HPP

enum class EvType
{
  NONE,
  WINDOW_CLOSE,
  //  WINDOW_RESIZE,
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
using KeyPressData = std::tuple<EvType, int>;
using KeyReleaseData = std::tuple<EvType, int>;
using MouseButtonPressData = std::tuple<EvType, int>;
using MouseButtonReleaseData = std::tuple<EvType, int>;
using MouseMoveData = std::tuple<EvType, float, float>;
using MouseScrollData = std::tuple<EvType, float, float>;

using EvData = std::variant<WindowCloseData,
                            KeyPressData,
                            KeyReleaseData,
                            MouseButtonPressData,
                            MouseButtonReleaseData,
                            MouseMoveData,
                            MouseScrollData>;

template <typename... Ts>
struct TypeGetter : Ts...
{
  using Ts::operator()...;
};

template <typename... Ts>
TypeGetter(Ts...) -> TypeGetter<Ts...>;

#endif // GRAPHICENGINE3D_GE_EVENT_TYPE_HPP
