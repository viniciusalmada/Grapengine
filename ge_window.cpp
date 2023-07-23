#include "ge_window.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

static bool glfw_initialized = false;

class Context
{
public:
  Context(GLFWwindow* glfWwindow) : m_window(glfWwindow) {}

  void Init()
  {
    glfwMakeContextCurrent(m_window);
    auto loader = [](const char* name)
    { return reinterpret_cast<void*>(glfwGetProcAddress(name)); };
    int status = gladLoadGLLoader(loader);
    if (!status)
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
  GLFWwindow* window;
  std::unique_ptr<Context> context;

  static void ErrorCB(int error_code, const char* description)
  {
    std::cerr << "Code:" << error_code << "\"" << description << "\"" << std::endl;
  }

  void Destroy() const
  {
    glfwDestroyWindow(window);
    glfwTerminate();
  }
};

//--PIMPL idiom
Window::Window(const WindowProps& props)
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
      glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);

  glfwSetWindowUserPointer(m_pimpl->window, this);

  m_pimpl->context = std::make_unique<Context>(m_pimpl->window);
  m_pimpl->context->Init();

  SetVsync(m_pimpl->vsync);
}

Window::~Window()
{
  m_pimpl->Destroy();
}

unsigned int Window::GetWidth() const
{
  return m_pimpl->window_props.width;
}

unsigned int Window::GetHeight() const
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
