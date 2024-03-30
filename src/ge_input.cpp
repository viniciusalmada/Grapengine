#include "input/ge_input.hpp"

#include "core/ge_window.hpp"

#include <GLFW/glfw3.h>
#include <core/ge_assert.hpp>
#include <imgui.h>

using namespace GE;

namespace
{
  std::optional<Input> input = std::nullopt;
}

struct Input::Impl
{
  Ref<Window> input_window = nullptr;
};

Input::Input(Ref<Window> window) : m_pimpl(MakeScope<Impl>())
{
  GE_INFO("Input polling creation");

  m_pimpl->input_window = window;
}

bool Input::IsKeyPressed(KeyCode keyCode)
{
  auto native_win = std::any_cast<GLFWwindow*>(m_pimpl->input_window->GetNativeHandler());
  int state = glfwGetKey(native_win, ConvertGEtoGFLW(keyCode));
  return state == GLFW_PRESS;
}

bool GE::Input::IsMouseButtonPressed(KeyCode keyCode)
{
  auto native_win = std::any_cast<GLFWwindow*>(m_pimpl->input_window->GetNativeHandler());
  int state = glfwGetMouseButton(native_win, ConvertGEtoGFLW(keyCode));
  return state == GLFW_PRESS;
}

Vec2 GE::Input::GetMouseXY()
{
  if (input_window == nullptr)
    return {};
  f64 x{}, y{};
  auto native_win = std::any_cast<GLFWwindow*>(m_pimpl->input_window->GetNativeHandler());
  glfwGetCursorPos(native_win, &x, &y);
  return Vec2((f32)x, (f32)y);
}
Input& GE::Input::Get()
{
  GE_ASSERT(input.has_value(), "Input not initialized")
  return *input;
}

void GE::Input::Initialize(Ref<Window> window)
{
  GE_ASSERT(!input.has_value(), "Input already initialized")
  input.emplace(Input{ std::move(window) });
}

void GE::Input::Shutdown()
{
  GE_ASSERT(input.has_value(), "Input not initialized")
  input = std::nullopt;
}
