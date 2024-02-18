#include "input/ge_input.hpp"

#include "core/ge_window.hpp"

#include <GLFW/glfw3.h>

using namespace GE;

struct Input::Impl
{
  Ref<Window> window;
};

Input::Input(Ref<Window> window) : m_pimpl(std::make_unique<Impl>())
{
  m_pimpl->window = window;
}

Input::~Input() = default;

bool Input::IsKeyPressed(KeyCode keyCode) const
{
  auto native_win = std::any_cast<GLFWwindow*>(m_pimpl->window->GetNativeHandler());
  int state = glfwGetKey(native_win, ConvertGEtoGFLW(keyCode));
  return state == GLFW_PRESS;
}

bool GE::Input::IsMouseButtonPressed(KeyCode keyCode) const
{
  auto native_win = std::any_cast<GLFWwindow*>(m_pimpl->window->GetNativeHandler());
  int state = glfwGetMouseButton(native_win, ConvertGEtoGFLW(keyCode));
  return state == GLFW_PRESS;
}

Vec2 GE::Input::GetMouseXY() const
{
  f64 x{}, y{};
  auto native_win = std::any_cast<GLFWwindow*>(m_pimpl->window->GetNativeHandler());
  glfwGetCursorPos(native_win, &x, &y);
  return Vec2((f32)x, (f32)y);
}
