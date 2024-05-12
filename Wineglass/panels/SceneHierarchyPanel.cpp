#include "SceneHierarchyPanel.hpp"

using namespace GE;

SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene) : m_scene_context(scene) {}

void SceneHierarchyPanel::SetContext(const Ref<Scene>& scene)
{
  m_scene_context = scene;
}

void SceneHierarchyPanel::OnImGuiRender()
{
  ImGui::Begin("Scene Hierarchy");
  m_scene_context->EachEntity([&](Entity ent) { DrawEntityNode(ent); });
  ImGui::End();

  ImGui::Begin("Properties");
  DrawComponents(m_selected_entity);
  ImGui::End();
}

void SceneHierarchyPanel::DrawEntityNode(Entity ent)
{
  void* node_id = TypeUtils::ToVoidPtr((i32)ent);
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

  if (m_scene_context->HasComponent<CameraComponent>(ent))
  {
    if (ImGui::TreeNodeEx(TypeUtils::ToVoidPtr(typeid(CameraComponent).hash_code()),
                          ImGuiTreeNodeFlags_DefaultOpen,
                          "CameraComponent"))
    {
      auto& comp = m_scene_context->GetComponent<CameraComponent>(ent);
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
