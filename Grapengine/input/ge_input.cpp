#include "input/ge_input.hpp"

#include "core/ge_assert.hpp"
#include "core/ge_window.hpp"

#include <GLFW/glfw3.h>

using namespace GE;

namespace
{
  Ref<Window> input_window = nullptr;
}

bool Input::IsKeyPressed(KeyCode keyCode)
{
  auto native_win = std::any_cast<GLFWwindow*>(input_window->GetNativeHandler());
  int state = glfwGetKey(native_win, ConvertGEtoGFLW(keyCode));
  return state == GLFW_PRESS;
}

bool GE::Input::IsMouseButtonPressed(KeyCode keyCode)
{
  auto native_win = std::any_cast<GLFWwindow*>(input_window->GetNativeHandler());
  int state = glfwGetMouseButton(native_win, ConvertGEtoGFLW(keyCode));
  return state == GLFW_PRESS;
}

Vec2 GE::Input::GetMouseXY()
{
  f64 x{}, y{};
  auto native_win = std::any_cast<GLFWwindow*>(input_window->GetNativeHandler());
  glfwGetCursorPos(native_win, &x, &y);
  return Vec2((f32)x, (f32)y);
}

void GE::Input::Initialize(Ref<Window> window)
{
  GE_INFO("Input polling creation")

  GE_ASSERT(input_window == nullptr, "Input already initialized")
  input_window = std::move(window);
}

void GE::Input::Shutdown()
{
  GE_ASSERT(input_window != nullptr, "Input not initialized")
  input_window = nullptr;
}
