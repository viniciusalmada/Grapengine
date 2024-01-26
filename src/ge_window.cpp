#include "core/ge_window.hpp"

#include "core/ge_assert.hpp"
#include "drawables/ge_canvas.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb_image.h>

using namespace GE;

static bool glfw_initialized = false;

namespace
{
  const std::map<i32, KeyCode> KEYS_LOOK_UP{
    { GLFW_KEY_SPACE, KeyCode::K_SPACE },
    { GLFW_KEY_APOSTROPHE, KeyCode::K_APOSTROPHE },
    { GLFW_KEY_COMMA, KeyCode::K_COMMA },
    { GLFW_KEY_MINUS, KeyCode::K_MINUS },
    { GLFW_KEY_PERIOD, KeyCode::K_PERIOD },
    { GLFW_KEY_SLASH, KeyCode::K_SLASH },
    { GLFW_KEY_0, KeyCode::K_0 },
    { GLFW_KEY_1, KeyCode::K_1 },
    { GLFW_KEY_2, KeyCode::K_2 },
    { GLFW_KEY_3, KeyCode::K_3 },
    { GLFW_KEY_4, KeyCode::K_4 },
    { GLFW_KEY_5, KeyCode::K_5 },
    { GLFW_KEY_6, KeyCode::K_6 },
    { GLFW_KEY_7, KeyCode::K_7 },
    { GLFW_KEY_8, KeyCode::K_8 },
    { GLFW_KEY_9, KeyCode::K_9 },
    { GLFW_KEY_SEMICOLON, KeyCode::K_SEMICOLON },
    { GLFW_KEY_EQUAL, KeyCode::K_EQUAL },
    { GLFW_KEY_A, KeyCode::K_A },
    { GLFW_KEY_B, KeyCode::K_B },
    { GLFW_KEY_C, KeyCode::K_C },
    { GLFW_KEY_D, KeyCode::K_D },
    { GLFW_KEY_E, KeyCode::K_E },
    { GLFW_KEY_F, KeyCode::K_F },
    { GLFW_KEY_G, KeyCode::K_G },
    { GLFW_KEY_H, KeyCode::K_H },
    { GLFW_KEY_I, KeyCode::K_I },
    { GLFW_KEY_J, KeyCode::K_J },
    { GLFW_KEY_K, KeyCode::K_K },
    { GLFW_KEY_L, KeyCode::K_L },
    { GLFW_KEY_M, KeyCode::K_M },
    { GLFW_KEY_N, KeyCode::K_N },
    { GLFW_KEY_O, KeyCode::K_O },
    { GLFW_KEY_P, KeyCode::K_P },
    { GLFW_KEY_Q, KeyCode::K_Q },
    { GLFW_KEY_R, KeyCode::K_R },
    { GLFW_KEY_S, KeyCode::K_S },
    { GLFW_KEY_T, KeyCode::K_T },
    { GLFW_KEY_U, KeyCode::K_U },
    { GLFW_KEY_V, KeyCode::K_V },
    { GLFW_KEY_W, KeyCode::K_W },
    { GLFW_KEY_X, KeyCode::K_X },
    { GLFW_KEY_Y, KeyCode::K_Y },
    { GLFW_KEY_Z, KeyCode::K_Z },
    { GLFW_KEY_LEFT_BRACKET, KeyCode::K_LEFT_BRACKET },
    { GLFW_KEY_BACKSLASH, KeyCode::K_BACKSLASH },
    { GLFW_KEY_RIGHT_BRACKET, KeyCode::K_RIGHT_BRACKET },
    { GLFW_KEY_GRAVE_ACCENT, KeyCode::K_GRAVE_ACCENT },
    { GLFW_KEY_ESCAPE, KeyCode::K_ESCAPE },
    { GLFW_KEY_ENTER, KeyCode::K_ENTER },
    { GLFW_KEY_TAB, KeyCode::K_TAB },
    { GLFW_KEY_BACKSPACE, KeyCode::K_BACKSPACE },
    { GLFW_KEY_INSERT, KeyCode::K_INSERT },
    { GLFW_KEY_DELETE, KeyCode::K_DELETE },
    { GLFW_KEY_RIGHT, KeyCode::K_RIGHT },
    { GLFW_KEY_LEFT, KeyCode::K_LEFT },
    { GLFW_KEY_DOWN, KeyCode::K_DOWN },
    { GLFW_KEY_UP, KeyCode::K_UP },
    { GLFW_KEY_PAGE_UP, KeyCode::K_PAGE_UP },
    { GLFW_KEY_PAGE_DOWN, KeyCode::K_PAGE_DOWN },
    { GLFW_KEY_HOME, KeyCode::K_HOME },
    { GLFW_KEY_END, KeyCode::K_END },
    { GLFW_KEY_CAPS_LOCK, KeyCode::K_CAPS_LOCK },
    { GLFW_KEY_SCROLL_LOCK, KeyCode::K_SCROLL_LOCK },
    { GLFW_KEY_NUM_LOCK, KeyCode::K_NUM_LOCK },
    { GLFW_KEY_PRINT_SCREEN, KeyCode::K_PRINT_SCREEN },
    { GLFW_KEY_PAUSE, KeyCode::K_PAUSE },
    { GLFW_KEY_F1, KeyCode::K_F1 },
    { GLFW_KEY_F2, KeyCode::K_F2 },
    { GLFW_KEY_F3, KeyCode::K_F3 },
    { GLFW_KEY_F4, KeyCode::K_F4 },
    { GLFW_KEY_F5, KeyCode::K_F5 },
    { GLFW_KEY_F6, KeyCode::K_F6 },
    { GLFW_KEY_F7, KeyCode::K_F7 },
    { GLFW_KEY_F8, KeyCode::K_F8 },
    { GLFW_KEY_F9, KeyCode::K_F9 },
    { GLFW_KEY_F10, KeyCode::K_F10 },
    { GLFW_KEY_F11, KeyCode::K_F11 },
    { GLFW_KEY_F12, KeyCode::K_F12 },
    { GLFW_KEY_F13, KeyCode::K_F13 },
    { GLFW_KEY_F14, KeyCode::K_F14 },
    { GLFW_KEY_F15, KeyCode::K_F15 },
    { GLFW_KEY_F16, KeyCode::K_F16 },
    { GLFW_KEY_F17, KeyCode::K_F17 },
    { GLFW_KEY_F18, KeyCode::K_F18 },
    { GLFW_KEY_F19, KeyCode::K_F19 },
    { GLFW_KEY_F20, KeyCode::K_F20 },
    { GLFW_KEY_F21, KeyCode::K_F21 },
    { GLFW_KEY_F22, KeyCode::K_F22 },
    { GLFW_KEY_F23, KeyCode::K_F23 },
    { GLFW_KEY_F24, KeyCode::K_F24 },
    { GLFW_KEY_F25, KeyCode::K_F25 },
    { GLFW_KEY_KP_0, KeyCode::K_KP_0 },
    { GLFW_KEY_KP_1, KeyCode::K_KP_1 },
    { GLFW_KEY_KP_2, KeyCode::K_KP_2 },
    { GLFW_KEY_KP_3, KeyCode::K_KP_3 },
    { GLFW_KEY_KP_4, KeyCode::K_KP_4 },
    { GLFW_KEY_KP_5, KeyCode::K_KP_5 },
    { GLFW_KEY_KP_6, KeyCode::K_KP_6 },
    { GLFW_KEY_KP_7, KeyCode::K_KP_7 },
    { GLFW_KEY_KP_8, KeyCode::K_KP_8 },
    { GLFW_KEY_KP_9, KeyCode::K_KP_9 },
    { GLFW_KEY_KP_DECIMAL, KeyCode::K_KP_DECIMAL },
    { GLFW_KEY_KP_DIVIDE, KeyCode::K_KP_DIVIDE },
    { GLFW_KEY_KP_MULTIPLY, KeyCode::K_KP_MULTIPLY },
    { GLFW_KEY_KP_SUBTRACT, KeyCode::K_KP_SUBTRACT },
    { GLFW_KEY_KP_ADD, KeyCode::K_KP_ADD },
    { GLFW_KEY_KP_ENTER, KeyCode::K_KP_ENTER },
    { GLFW_KEY_KP_EQUAL, KeyCode::K_KP_EQUAL },
    { GLFW_KEY_LEFT_SHIFT, KeyCode::K_LEFT_SHIFT },
    { GLFW_KEY_LEFT_CONTROL, KeyCode::K_LEFT_CONTROL },
    { GLFW_KEY_LEFT_ALT, KeyCode::K_LEFT_ALT },
    { GLFW_KEY_LEFT_SUPER, KeyCode::K_LEFT_SUPER },
    { GLFW_KEY_RIGHT_SHIFT, KeyCode::K_RIGHT_SHIFT },
    { GLFW_KEY_RIGHT_CONTROL, KeyCode::K_RIGHT_CONTROL },
    { GLFW_KEY_RIGHT_ALT, KeyCode::K_RIGHT_ALT },
    { GLFW_KEY_RIGHT_SUPER, KeyCode::K_RIGHT_SUPER },
    { GLFW_KEY_MENU, KeyCode::K_MENU },
    { GLFW_MOUSE_BUTTON_1, KeyCode::MOUSE_BT_LEFT },
    { GLFW_MOUSE_BUTTON_2, KeyCode::MOUSE_BT_RIGHT },
    { GLFW_MOUSE_BUTTON_3, KeyCode::MOUSE_BT_MIDDLE },
    { GLFW_KEY_UNKNOWN, KeyCode::K_NONE },
  };

  KeyCode GetKey(i32 k)
  {
    return KEYS_LOOK_UP.at(k);
  }
}

class Context
{
public:
  explicit Context(GLFWwindow* glfWwindow) : m_window(glfWwindow) {}

  void Init()
  {
    glfwMakeContextCurrent(m_window);

    i32 version = gladLoadGL();
    if (version == 0)
      throw std::runtime_error("Error with GLAD");

    std::cout << "OpenGL Vendor: " << (char*)glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL Renderer: " << (char*)glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version: " << (char*)glGetString(GL_VERSION) << std::endl;
  }

  void SwapBuffers() { glfwSwapBuffers(m_window); }

private:
  GLFWwindow* m_window;
};

//--PIMPL idiom
struct Window::Impl
{
  Scope<WindowProps> window_props;
  bool vsync = true;
  GLFWwindow* window = nullptr;
  Scope<Context> context;
  EventCallbackFn event_callback;
  Ref<Canvas> canvas;

  static void ErrorCB(i32 error_code, const char* description)
  {
    std::stringstream ss;
    ss << "Code:" << error_code << "\"" << description << "\"" << std::endl;
    Assert(false, ss.str().c_str());
  }

  void Destroy() const
  {
    glfwDestroyWindow(window);
    glfwTerminate();
  }
};

//--PIMPL idiom
Window::Window(const WindowProps& props, const EventCallbackFn& cb) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->window_props =
    MakeScope<WindowProps>(props.title, props.width, props.height, props.icon_path);
  if (!glfw_initialized)
  {
    auto success = glfwInit();
    if (!success)
      throw std::runtime_error("Error GLFW");

    glfwSetErrorCallback(Impl::ErrorCB);

    glfw_initialized = true;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  m_pimpl->window =
    glfwCreateWindow((i32)props.width, (i32)props.height, props.title.c_str(), nullptr, nullptr);
  glfwSetWindowAspectRatio(m_pimpl->window, props.width, props.height);

  GLFWimage image;
  image.pixels = stbi_load(props.icon_path.c_str(), &image.width, &image.height, nullptr, 4);
  glfwSetWindowIcon(m_pimpl->window, 1, &image);
  stbi_image_free(image.pixels);

  glfwSetWindowUserPointer(m_pimpl->window, this);

  m_pimpl->canvas = MakeRef<Canvas>(props.width, props.height);

  m_pimpl->context = MakeScope<Context>(m_pimpl->window);
  m_pimpl->context->Init();

  SetVsync(m_pimpl->vsync);

  if (cb)
  {
    m_pimpl->event_callback = cb;

    //-----------------------------
    auto close_callback = [](GLFWwindow* win)
    {
      Event event{ std::make_tuple(EvType::WINDOW_CLOSE) };
      auto* data = (Window*)glfwGetWindowUserPointer(win);
      data->m_pimpl->event_callback(event);
    };
    glfwSetWindowCloseCallback(m_pimpl->window, close_callback);

    //-----------------------------
    auto resize_callback = [](GLFWwindow* win, i32 width, i32 height)
    {
      Event event{ std::make_tuple(EvType::WINDOW_RESIZE, width, height) };
      auto* data = (Window*)glfwGetWindowUserPointer(win);
      data->m_pimpl->event_callback(event);
      data->m_pimpl->window_props->width = width;
      data->m_pimpl->window_props->height = height;
    };
    glfwSetWindowSizeCallback(m_pimpl->window, resize_callback);

    //-----------------------------
    auto key_callback = [](GLFWwindow* win, i32 key, i32 /*scancode*/, i32 action, i32 /*mods*/)
    {
      EvType type = EvType::NONE;
      if (action == GLFW_PRESS)
        type = EvType::KEY_PRESS;
      else if (action == GLFW_RELEASE)
        type = EvType::KEY_RELEASE;

      Event event{ std::make_tuple(type, GetKey(key)) };
      auto* data = (Window*)glfwGetWindowUserPointer(win);
      data->m_pimpl->event_callback(event);
    };
    glfwSetKeyCallback(m_pimpl->window, key_callback);

    //-----------------------------
    auto mouse_bt_callback = [](GLFWwindow* win, i32 button, i32 action, i32 /*mods*/)
    {
      EvType type = EvType::NONE;
      if (action == GLFW_PRESS)
        type = EvType::MOUSE_BUTTON_PRESSED;
      else if (action == GLFW_RELEASE)
        type = EvType::MOUSE_BUTTON_RELEASE;

      Event event{ std::make_tuple(type, GetKey(button)) };
      auto* data = (Window*)glfwGetWindowUserPointer(win);
      data->m_pimpl->event_callback(event);
    };
    glfwSetMouseButtonCallback(m_pimpl->window, mouse_bt_callback);

    //-----------------------------
    auto mouse_move = [](GLFWwindow* win, double xpos, double ypos)
    {
      Event event{ std::make_tuple(EvType::MOUSE_MOVE, (float)xpos, (float)ypos) };
      auto* data = (Window*)glfwGetWindowUserPointer(win);
      data->m_pimpl->event_callback(event);
    };
    glfwSetCursorPosCallback(m_pimpl->window, mouse_move);

    //-----------------------------
    auto mouse_scroll = [](GLFWwindow* win, double xoffset, double yoffset)
    {
      Event event{ std::make_tuple(EvType::MOUSE_SCROLL, (float)xoffset, (float)yoffset) };
      auto* data = (Window*)glfwGetWindowUserPointer(win);
      data->m_pimpl->event_callback(event);
    };
    glfwSetScrollCallback(m_pimpl->window, mouse_scroll);
  }
}

Window::~Window()
{
  m_pimpl->Destroy();
  glfw_initialized = false;
}

u32 Window::GetWidth() const
{
  return m_pimpl->window_props->width;
}

u32 Window::GetHeight() const
{
  return m_pimpl->window_props->height;
}

void Window::SetVsync(bool enabled)
{
  glfwSwapInterval(enabled ? 1 : 0);

  m_pimpl->vsync = enabled;
}

void Window::OnUpdate()
{
  glfwPollEvents();
  m_pimpl->context->SwapBuffers();
}

void Window::Clear(Color color) const
{
  m_pimpl->canvas->Clear(color.ToVec4());
}

void Window::Draw(Ref<Drawable> drawable) const
{
  m_pimpl->canvas->Draw(std::move(drawable));
}

Vec2 Window::GetCursorPos() const
{
  double x{}, y{};
  glfwGetCursorPos(m_pimpl->window, &x, &y);
  return Vec2((float)x, (float)y);
}
