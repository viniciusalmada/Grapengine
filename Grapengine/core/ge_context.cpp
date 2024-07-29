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
  GE_ASSERT_OR_RETURN_VOID(version != 0, "Failed to initialize OpenGL context");

  // NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
  GE_INFO("OpenGL INFO BEGIN-----------------------------------")
  GE_INFO("OpenGL Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)))
  GE_INFO("OpenGL Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)))
  GE_INFO("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)))
  GE_INFO("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)))
  int max_compute_uniform_blocks;
  glGetIntegerv(GL_MAX_COMPUTE_UNIFORM_COMPONENTS, &max_compute_uniform_blocks);
  GE_INFO("  GL_MAX_COMPUTE_UNIFORM_COMPONENTS: {}", max_compute_uniform_blocks)
  GE_INFO("OpenGL INFO END-----------------------------------")
  // NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
}

void Context::SwapBuffers()
{
  glfwSwapBuffers(m_window);
}

Context::Context() : Context(nullptr) {}
