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

  m_scene_context->Registry().Each(
    [&](Entity ent)
    {
      auto tag = m_scene_context->Registry().GetComponent<TagComponent>(ent);
      ImGui::Text("%s", tag.tag);
    });

  ImGui::End();
}
