#include "core/ge_window.hpp"

#include "core/ge_assert.hpp"
#include "drawables/ge_canvas.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb_image.h>

using namespace GE;

namespace
{
  bool glfw_initialized = false;

  void ErrorCB(i32 error_code, const char* description)
  {
    GE::Assert(false, "Code: {} \'{}\'", error_code, description);
  }
}

Window::Window(const WindowProps& props, const EventCallbackFn& cb) : m_window_props(props)
{
  //  GE_INFO("Window creation")

  if (!glfw_initialized)
  {
    GE_INFO("GLFW initialization")
    auto success = glfwInit();
    if (!success)
      throw std::runtime_error("Error GLFW");

    glfwSetErrorCallback(ErrorCB);

    glfw_initialized = true;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  m_window =
    glfwCreateWindow(i32(props.width), i32(props.height), props.title.c_str(), nullptr, nullptr);
  //  glfwSetWindowAspectRatio(m_window,
  //                           static_cast<i32>(props.width),
  //                           static_cast<i32>(props.height));

  GLFWimage image;
  image.pixels = stbi_load(props.icon_path.c_str(), &image.width, &image.height, nullptr, 4);
  glfwSetWindowIcon(m_window, 1, &image);
  stbi_image_free(image.pixels);

  glfwSetWindowUserPointer(m_window, this);

  m_canvas = MakeRef<Canvas>(props.width, props.height);

  m_context = Context{ m_window };
  m_context.Init();

  SetVsync(m_vsync);

  if (cb)
    SetupCallbacks(cb);
}

Window::~Window()
{
  GE_INFO("Window destroy")

  glfwDestroyWindow(m_window);
  glfwTerminate();
  glfw_initialized = false;
}

u32 Window::GetWidth() const
{
  return m_window_props.width;
}

u32 Window::GetHeight() const
{
  return m_window_props.height;
}

void Window::SetVsync(bool enabled)
{
  glfwSwapInterval(enabled ? 1 : 0);

  m_vsync = enabled;
}

void Window::OnUpdate()
{
  glfwPollEvents();
  m_context.SwapBuffers();
}

void Window::Clear(Color color) const
{
  m_canvas->Clear(color.ToVec4());
}

void Window::Draw(const Ref<Drawable>& drawable) const
{
  m_canvas->Draw(drawable);
}

std::any Window::GetNativeHandler() const
{
  return std::make_any<GLFWwindow*>(m_window);
}

void Window::SetupCallbacks(const EventCallbackFn& cb)
{
  GE_INFO("Window callbacks setup")

  m_event_callback = cb;

  //-----------------------------
  auto close_callback = [](GLFWwindow* win)
  {
    Event event{ EvType::WINDOW_CLOSE };
    auto* data = static_cast<Window*>(glfwGetWindowUserPointer(win));
    data->m_event_callback(event);
  };
  glfwSetWindowCloseCallback(m_window, close_callback);

  //-----------------------------
  auto resize_callback = [](GLFWwindow* win, i32 width, i32 height)
  {
    Event event{ EvType::WINDOW_RESIZE,
                 std::make_pair(static_cast<u32>(width), static_cast<u32>(height)) };
    auto* data = static_cast<Window*>(glfwGetWindowUserPointer(win));
    data->m_event_callback(event);
    data->m_window_props.width = static_cast<u32>(width);
    data->m_window_props.height = static_cast<u32>(height);
  };
  glfwSetWindowSizeCallback(m_window, resize_callback);

  //-----------------------------
  auto key_callback = [](GLFWwindow* win, i32 key, i32 /*scancode*/, i32 action, i32 /*mods*/)
  {
    EvType type = EvType::NONE;
    if (action == GLFW_PRESS)
      type = EvType::KEY_PRESS;
    else if (action == GLFW_RELEASE)
      type = EvType::KEY_RELEASE;

    Event event{ type, Keys::ConvertGLFWtoGE(key) };
    auto* data = static_cast<Window*>(glfwGetWindowUserPointer(win));
    data->m_event_callback(event);
  };
  glfwSetKeyCallback(m_window, key_callback);

  //-----------------------------
  auto mouse_bt_callback = [](GLFWwindow* win, i32 button, i32 action, i32 /*mods*/)
  {
    //      if (ImGui::GetIO().WantCaptureMouse)
    //        return;
    EvType type = EvType::NONE;
    if (action == GLFW_PRESS)
      type = EvType::MOUSE_BUTTON_PRESSED;
    else if (action == GLFW_RELEASE)
      type = EvType::MOUSE_BUTTON_RELEASE;

    Event event{ type, Keys::ConvertGLFWtoGE(button) };
    auto* data = static_cast<Window*>(glfwGetWindowUserPointer(win));
    data->m_event_callback(event);
  };
  glfwSetMouseButtonCallback(m_window, mouse_bt_callback);

  //-----------------------------
  auto mouse_move = [](GLFWwindow* win, f64 xpos, f64 ypos)
  {
    Event event{ EvType::MOUSE_MOVE, std::make_pair(f32(xpos), f32(ypos)) };
    auto* data = static_cast<Window*>(glfwGetWindowUserPointer(win));
    data->m_event_callback(event);
  };
  glfwSetCursorPosCallback(m_window, mouse_move);

  //-----------------------------
  auto mouse_scroll = [](GLFWwindow* win, f64 xoffset, f64 yoffset)
  {
    //      if (ImGui::GetIO().WantCaptureMouse)
    //        return;
    Event event{ EvType::MOUSE_SCROLL, std::make_pair(f32(xoffset), f32(yoffset)) };
    auto* data = static_cast<Window*>(glfwGetWindowUserPointer(win));
    data->m_event_callback(event);
  };
  glfwSetScrollCallback(m_window, mouse_scroll);
}

Ref<Window> Window::Make(const WindowProps& props, const EventCallbackFn& cb)
{
  return MakeRef<Window>(props, cb);
}
