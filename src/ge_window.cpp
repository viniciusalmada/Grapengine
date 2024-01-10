#include "core/ge_window.hpp"

#include "core/ge_assert.hpp"
#include "drawables/ge_canvas.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

static bool glfw_initialized = false;

class Context
{
public:
  explicit Context(GLFWwindow* glfWwindow) : m_window(glfWwindow) {}

  void Init()
  {
    glfwMakeContextCurrent(m_window);

    i32 version = gladLoadGL();
    if (version == 0)
      throw std::exception("Error with GLAD");

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
  WindowProps window_props{};
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
  m_pimpl->window_props = props;
  if (!glfw_initialized)
  {
    auto success = glfwInit();
    if (!success)
      throw std::exception("Error GLFW");

    glfwSetErrorCallback(Impl::ErrorCB);

    glfw_initialized = true;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  m_pimpl->window =
    glfwCreateWindow((i32)props.width, (i32)props.height, props.title.c_str(), nullptr, nullptr);

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

      Event event{ std::make_tuple(type, key) };
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

      Event event{ std::make_tuple(type, button) };
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
  return m_pimpl->window_props.width;
}

u32 Window::GetHeight() const
{
  return m_pimpl->window_props.height;
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
