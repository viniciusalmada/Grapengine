#ifndef GRAPENGINE_GE_KEY_CODES_HPP
#define GRAPENGINE_GE_KEY_CODES_HPP

#include <map>

namespace GE
{
  enum class KeyCode : u8
  {
    MOUSE_BT_RIGHT,
    MOUSE_BT_LEFT,
    MOUSE_BT_MIDDLE,
    /* Printable keys */
    SPACE,
    APOSTROPHE, /* ' */
    COMMA,      /* , */
    MINUS,      /* - */
    PERIOD,     /* . */
    SLASH,      /* / */
    D0,
    D1,
    D2,
    D3,
    D4,
    D5,
    D6,
    D7,
    D8,
    D9,
    SEMICOLON, /* ; */
    EQUAL,     /* = */
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    LEFT_BRACKET,  /* [ */
    BACKSLASH,     /* \ */
    RIGHT_BRACKET, /* ] */
    GRAVE_ACCENT,  /* ` */
    ESCAPE,
    ENTER,
    TAB,
    BACKSPACE,
    INSERT,
    DEL,
    RIGHT,
    LEFT,
    DOWN,
    UP,
    PAGE_UP,
    PAGE_DOWN,
    HOME,
    END,
    CAPS_LOCK,
    SCROLL_LOCK,
    NUM_LOCK,
    PRINT_SCREEN,
    PAUSE,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    F25,
    KP_0,
    KP_1,
    KP_2,
    KP_3,
    KP_4,
    KP_5,
    KP_6,
    KP_7,
    KP_8,
    KP_9,
    KP_DECIMAL,
    KP_DIVIDE,
    KP_MULTIPLY,
    KP_SUBTRACT,
    KP_ADD,
    KP_ENTER,
    KP_EQUAL,
    LEFT_SHIFT,
    LEFT_CONTROL,
    LEFT_ALT,
    LEFT_SUPER,
    RIGHT_SHIFT,
    RIGHT_CONTROL,
    RIGHT_ALT,
    RIGHT_SUPER,
    MENU,
    NONE,
  };

  class Keys
  {
  public:
    static KeyCode ConvertGLFWtoGE(i32 code);

    static i32 ConvertGEtoGFLW(KeyCode code);

  private:
    Keys();

    static Keys& Get();

    std::map<i32, KeyCode> m_glfw_to_ge;
    std::map<KeyCode, i32> m_ge_to_glfw;
  };
}

#endif // GRAPENGINE_GE_KEY_CODES_HPP
