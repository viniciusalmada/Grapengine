#include "input/ge_input.hpp"

#include "core/ge_window.hpp"

#include <GLFW/glfw3.h>

using namespace GE;

namespace
{
  Ref<Window> input_window = nullptr;
}

Input::Input(Ref<Window> window)
{
  input_window = std::move(window);
}

Input::~Input() = default;

bool Input::IsKeyPressed(KeyCode keyCode)
{
  if (input_window == nullptr)
    return false;
  auto native_win = std::any_cast<GLFWwindow*>(input_window->GetNativeHandler());
  int state = glfwGetKey(native_win, ConvertGEtoGFLW(keyCode));
  return state == GLFW_PRESS;
}

bool GE::Input::IsMouseButtonPressed(KeyCode keyCode)
{
  if (input_window == nullptr)
    return false;
  auto native_win = std::any_cast<GLFWwindow*>(input_window->GetNativeHandler());
  int state = glfwGetMouseButton(native_win, ConvertGEtoGFLW(keyCode));
  return state == GLFW_PRESS;
}

Vec2 GE::Input::GetMouseXY()
{
  if (input_window == nullptr)
    return {};
  f64 x{}, y{};
  auto native_win = std::any_cast<GLFWwindow*>(input_window->GetNativeHandler());
  glfwGetCursorPos(native_win, &x, &y);
  return Vec2((f32)x, (f32)y);
}
