#ifndef GRAPENGINE_GE_CONTEXT_HPP
#define GRAPENGINE_GE_CONTEXT_HPP

#include <GLFW/glfw3.h>

namespace GE
{
  class Context
  {
  public:
    explicit Context();
    explicit Context(GLFWwindow* glfWwindow);

    void Init();

    void SwapBuffers();

  private:
    GLFWwindow* m_window;
  };

} // GE

#endif // GRAPENGINE_GE_CONTEXT_HPP
