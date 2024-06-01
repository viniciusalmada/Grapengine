#include "SceneHierarchyPanel.hpp"

using namespace std::string_literals;
using namespace GE;

SceneHierarchyPanel::SceneHierarchyPanel(const Ptr<Scene>& scene) : m_scene_context(scene) {}

void SceneHierarchyPanel::SetContext(const Ptr<Scene>& scene)
{
  m_scene_context = scene;
}

void SceneHierarchyPanel::OnImGuiRender()
{
  ImGui::Begin("Scene Hierarchy");
  m_scene_context->EachEntity([&](Entity ent) { DrawEntityNode(ent); });

  if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
    m_selected_entity = {};

  ImGui::End();

  ImGui::Begin("Properties");
  DrawComponents(m_selected_entity);
  ImGui::End();

  ImGui::ShowDemoWindow(nullptr);
}

void SceneHierarchyPanel::DrawEntityNode(Entity ent)
{
  void* node_id = TypeUtils::ToVoidPtr(i32(ent));
  const int is_selected = ent == m_selected_entity ? ImGuiTreeNodeFlags_Selected : 0;
  const int flags = is_selected | ImGuiTreeNodeFlags_OpenOnArrow;

  auto& tag = m_scene_context->GetComponent<TagComponent>(ent);
  bool expanded = ImGui::TreeNodeEx(node_id, flags, "%s", tag.tag.c_str());

  if (ImGui::IsItemClicked())
  {
    m_selected_entity = ent;
  }

  if (expanded)
  {
    bool expanded2 = ImGui::TreeNodeEx(TypeUtils::ToVoidPtr(1434 + i32(ent)),
                                       ImGuiTreeNodeFlags_None,
                                       "%s",
                                       tag.tag.c_str());
    if (expanded2)
      ImGui::TreePop();
    ImGui::TreePop();
  }
}

void SceneHierarchyPanel::DrawComponents(Entity ent)
{
  if (m_scene_context->HasComponent<TagComponent>(ent))
  {
    auto& tag = m_scene_context->GetComponent<TagComponent>(ent).tag;

    constexpr auto BUFFER_SIZE = 256;
    std::array<char, BUFFER_SIZE> buffer{ '\0' };
    std::ranges::copy(tag, buffer.begin());
    if (ImGui::InputText("Tag",
                         buffer.data(),
                         sizeof(buffer),
                         ImGuiInputTextFlags_EnterReturnsTrue))
    {
      tag = std::string(buffer.data());
    }
  }

  if (m_scene_context->HasComponent<TranslateScaleComponent>(ent))
  {
    if (ImGui::TreeNodeEx(TypeUtils::ToVoidPtr(typeid(TranslateScaleComponent).hash_code()),
                          ImGuiTreeNodeFlags_DefaultOpen,
                          "TranslateAndScale"))
    {
      auto& pos = m_scene_context->GetComponent<TranslateScaleComponent>(ent).position_values;
      auto& scale = m_scene_context->GetComponent<TranslateScaleComponent>(ent).scale_values;

      ImGui::DragFloat3("Position", &pos.x, 0.01f);
      ImGui::DragFloat3("Scale", &scale.x, 0.01f);

      ImGui::TreePop();
    }
  }

  if (m_scene_context->HasComponent<PrimitiveComponent>(ent))
  {
    auto& cube_color = m_scene_context->GetComponent<PrimitiveComponent>(ent).color;

    static Vec4 imgui_color{};
    imgui_color = cube_color.ToVec4();

    ImGui::ColorEdit4("Color", &imgui_color.x0);

    cube_color = Color(imgui_color);
  }

  if (m_scene_context->HasComponent<CameraComponent>(ent))
  {
    if (ImGui::TreeNodeEx(TypeUtils::ToVoidPtr(typeid(CameraComponent).hash_code()),
                          ImGuiTreeNodeFlags_DefaultOpen,
                          "CameraComponent"))
    {
      auto& comp = m_scene_context->GetComponent<CameraComponent>(ent);

      if (ImGui::Checkbox("Active", &comp.active))
      {
        comp.active = true;
        m_scene_context->UpdateActiveCamera(ent);
      }
      ImGui::Checkbox("Fixed AR", &comp.fixed_ratio);

      const std::array TITLES{ "Perspective"s, "Orthographic"s };
      u8 current_mode = u8(comp.camera.GetProjectionMode());
      const char* preview_value = TITLES.at(current_mode).c_str();
      if (ImGui::BeginCombo("Projection", preview_value))
      {
        for (u32 n = 0; n < TITLES.size(); n++)
        {
          const bool is_selected = (current_mode == n);
          if (ImGui::Selectable(TITLES.at(n).c_str(), is_selected))
          {
            current_mode = u8(n);
            comp.camera.SetProjectionMode(ProjectionMode(current_mode));
          }

          if (is_selected)
            ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
      }

      if (comp.camera.IsInProjectionMode(ProjectionMode::PERSPECTIVE))
      {
        f32 fov = comp.camera.GetFov();
        if (ImGui::DragFloat("FOV",
                             &fov,
                             10.0f,
                             30.0f,
                             100.0f,
                             "%1.0f deg",
                             ImGuiSliderFlags_AlwaysClamp))
          comp.camera.SetFov(fov);
      }

      if (comp.camera.IsInProjectionMode(ProjectionMode::ORTHO))
      {
        f32 size = comp.camera.GetOrthographicSize();
        if (ImGui::DragFloat("Size",
                             &size,
                             10.0f,
                             5.0f,
                             100.0f,
                             "%1.0f",
                             ImGuiSliderFlags_AlwaysClamp))
          comp.camera.SetOrthographicSize(size);
      }

      Vec3 eye = comp.camera.GetPosition();
      Vec3 target = comp.camera.GetTarget();

      bool changed_eye = ImGui::DragFloat3("Eye", &eye.x, 0.01f);
      bool changed_target = ImGui::DragFloat3("Target", &target.x, 0.01f);

      if (changed_eye || changed_target)
        comp.camera.SetView(eye, target);

      ImGui::TreePop();
    }
  }
}
