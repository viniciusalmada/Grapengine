#include "input/ge_input.hpp"

#include "core/ge_assert.hpp"
#include "core/ge_window.hpp"

#include <GLFW/glfw3.h>

using namespace GE;

bool Input::IsKeyPressed(KeyCode keyCode)
{
  auto native_win = std::any_cast<GLFWwindow*>(Get().m_windows->GetNativeHandler());
  int state = glfwGetKey(native_win, Keys::ConvertGEtoGFLW(keyCode));
  return state == GLFW_PRESS;
}

bool GE::Input::IsMouseButtonPressed(KeyCode keyCode)
{
  auto native_win = std::any_cast<GLFWwindow*>(Get().m_windows->GetNativeHandler());
  int state = glfwGetMouseButton(native_win, Keys::ConvertGEtoGFLW(keyCode));
  return state == GLFW_PRESS;
}

Vec2 GE::Input::GetMouseXY()
{
  f64 x{}, y{};
  auto native_win = std::any_cast<GLFWwindow*>(Get().m_windows->GetNativeHandler());
  glfwGetCursorPos(native_win, &x, &y);
  return Vec2{ f32(x), f32(y) };
}

void GE::Input::Initialize(Ref<Window> window)
{
  GE_INFO("Input polling creation")

  GE_ASSERT(Get().m_windows == nullptr, "Input already initialized")
  Get().m_windows = std::move(window);
}

void GE::Input::Shutdown()
{
  GE_ASSERT(Get().m_windows != nullptr, "Input not initialized")
  Get().m_windows = nullptr;
}

Input& Input::Get()
{
  static Input input;
  return input;
}
