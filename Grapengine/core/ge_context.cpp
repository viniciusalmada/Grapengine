#include "ge_context.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

using namespace GE;

Context::Context(GLFWwindow* glfWwindow) : m_window(glfWwindow)
{
  GE_INFO("Context creation")
}

void Context::Init()
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

void Context::SwapBuffers()
{
  glfwSwapBuffers(m_window);
}

Context::Context() : Context(nullptr) {}
