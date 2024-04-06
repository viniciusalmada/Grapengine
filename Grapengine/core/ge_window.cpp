#include "core/ge_window.hpp"

#include "core/ge_assert.hpp"
#include "drawables/ge_canvas.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb_image.h>

using namespace GE;

static bool glfw_initialized = false;

class Context
{
public:
  explicit Context(GLFWwindow* glfWwindow) : m_window(glfWwindow) { GE_INFO("Context creation") }

  void Init()
  {
    glfwMakeContextCurrent(m_window);

    i32 version = gladLoadGL();
    GE_INFO("GLAD initialization: {}", version)
    if (version == 0)
      throw std::runtime_error("Error with GLAD");

    GE_INFO("OpenGL Vendor: {}", (char*)glGetString(GL_VENDOR))
    GE_INFO("OpenGL Renderer: {}", (char*)glGetString(GL_RENDERER))
    GE_INFO("OpenGL Version: {}", (char*)glGetString(GL_VERSION))
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
    GE_ASSERT(false, ss.str().c_str());
  }

  void SetupCallbacks(const EventCallbackFn& cb)
  {
    GE_INFO("Window callbacks setup")

    event_callback = cb;

    //-----------------------------
    auto close_callback = [](GLFWwindow* win)
    {
      Event event{ EvType::WINDOW_CLOSE };
      auto* data = (Window*)glfwGetWindowUserPointer(win);
      data->m_pimpl->event_callback(event);
    };
    glfwSetWindowCloseCallback(window, close_callback);

    //-----------------------------
    auto resize_callback = [](GLFWwindow* win, i32 width, i32 height)
    {
      Event event{ EvType::WINDOW_RESIZE,
                   std::make_pair(static_cast<u32>(width), static_cast<u32>(height)) };
      auto* data = (Window*)glfwGetWindowUserPointer(win);
      data->m_pimpl->event_callback(event);
      data->m_pimpl->window_props->width = static_cast<u32>(width);
      data->m_pimpl->window_props->height = static_cast<u32>(height);
    };
    glfwSetWindowSizeCallback(window, resize_callback);

    //-----------------------------
    auto key_callback = [](GLFWwindow* win, i32 key, i32 /*scancode*/, i32 action, i32 /*mods*/)
    {
      EvType type = EvType::NONE;
      if (action == GLFW_PRESS)
        type = EvType::KEY_PRESS;
      else if (action == GLFW_RELEASE)
        type = EvType::KEY_RELEASE;

      Event event{ type, ConvertGLFWtoGE(key) };
      auto* data = (Window*)glfwGetWindowUserPointer(win);
      data->m_pimpl->event_callback(event);
    };
    glfwSetKeyCallback(window, key_callback);

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

      Event event{ type, ConvertGLFWtoGE(button) };
      auto* data = (Window*)glfwGetWindowUserPointer(win);
      data->m_pimpl->event_callback(event);
    };
    glfwSetMouseButtonCallback(window, mouse_bt_callback);

    //-----------------------------
    auto mouse_move = [](GLFWwindow* win, f64 xpos, f64 ypos)
    {
      Event event{ EvType::MOUSE_MOVE, std::make_pair((f32)xpos, (f32)ypos) };
      auto* data = (Window*)glfwGetWindowUserPointer(win);
      data->m_pimpl->event_callback(event);
    };
    glfwSetCursorPosCallback(window, mouse_move);

    //-----------------------------
    auto mouse_scroll = [](GLFWwindow* win, f64 xoffset, f64 yoffset)
    {
      //      if (ImGui::GetIO().WantCaptureMouse)
      //        return;
      Event event{ EvType::MOUSE_SCROLL, std::make_pair((f32)xoffset, (f32)yoffset) };
      auto* data = (Window*)glfwGetWindowUserPointer(win);
      data->m_pimpl->event_callback(event);
    };
    glfwSetScrollCallback(window, mouse_scroll);
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
  GE_INFO("Window creation")

  m_pimpl->window_props =
    MakeScope<WindowProps>(props.title, props.width, props.height, props.icon_path);
  if (!glfw_initialized)
  {
    GE_INFO("GLFW initialization")
    auto success = glfwInit();
    if (!success)
      throw std::runtime_error("Error GLFW");

    glfwSetErrorCallback(Impl::ErrorCB);

    glfw_initialized = true;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  m_pimpl->window =
    glfwCreateWindow((i32)props.width, (i32)props.height, props.title.c_str(), nullptr, nullptr);
  //  glfwSetWindowAspectRatio(m_pimpl->window,
  //                           static_cast<i32>(props.width),
  //                           static_cast<i32>(props.height));

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
    m_pimpl->SetupCallbacks(cb);
}

Window::~Window()
{
  GE_INFO("Window destroy")

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

void Window::Draw(const Ref<Drawable>& drawable) const
{
  m_pimpl->canvas->Draw(drawable);
}

std::any GE::Window::GetNativeHandler() const
{
  return std::make_any<GLFWwindow*>(m_pimpl->window);
}
