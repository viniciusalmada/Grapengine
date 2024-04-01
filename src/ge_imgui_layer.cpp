#include "layer/ge_imgui_layer.hpp"

#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <core/ge_time_step.hpp>
#include <imgui.h>

#undef USE_MULTIPLE_VIEWPORTS

using namespace GE;

namespace
{
  constexpr auto IMGUI_LAYER = "IMGUI_LAYER";
}

struct ImGuiLayer::Impl
{
  Ref<Window> window = nullptr;
};

ImGuiLayer::ImGuiLayer(Ref<Window> window) : Layer(IMGUI_LAYER), m_pimpl(MakeScope<Impl>())
{
  m_pimpl->window = std::move(window);
}

ImGuiLayer::~ImGuiLayer() = default;

void ImGuiLayer::OnAttach()
{
  GE_INFO("ImGui initialization")

  Layer::OnAttach();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
#ifdef USE_MULTIPLE_VIEWPORTS
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
#endif

  ImGui_ImplGlfw_InitForOpenGL(std::any_cast<GLFWwindow*>(m_pimpl->window->GetNativeHandler()),
                               true);
  ImGui_ImplOpenGL3_Init();
}
void ImGuiLayer::OnDetach()
{
  GE_INFO("ImGui shutdown")

  Layer::OnDetach();

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}
void ImGuiLayer::Begin()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

Ref<ImGuiLayer> ImGuiLayer::Make(Ref<Window> window)
{
  return MakeRef<ImGuiLayer>(std::move(window));
}

void ImGuiLayer::End()
{
  auto& io = ImGui::GetIO();
  io.DisplaySize = ImVec2(static_cast<f32>(m_pimpl->window->GetWidth()),
                          static_cast<float>(m_pimpl->window->GetWidth()));

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

#ifdef USE_MULTIPLE_VIEWPORTS
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    GLFWwindow* backup_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_context);
  }
#endif
}
