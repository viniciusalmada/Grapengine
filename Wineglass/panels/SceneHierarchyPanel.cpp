#include "SceneHierarchyPanel.hpp"

#include <imgui_internal.h>

using namespace std::string_literals;
using namespace GE;

namespace
{
  constexpr auto MAX_COLOR = 255.0f;

  struct C
  {
    f32 c;
    constexpr C(u8 u) : c(f32(u) / MAX_COLOR) {}
  };

  constexpr f32 XN_R = C{ 0xB2 }.c; // X normal
  constexpr f32 XN_G = C{ 0x0F }.c; // X normal
  constexpr f32 XN_B = C{ 0x0F }.c; // X normal
  constexpr f32 XH_R = C{ 0xC2 }.c; // X hovered
  constexpr f32 XH_G = C{ 0x0F }.c; // X hovered
  constexpr f32 XH_B = C{ 0x0F }.c; // X hovered
  constexpr f32 XA_R = C{ 0xB2 }.c; // X active
  constexpr f32 XA_G = C{ 0x1F }.c; // X active
  constexpr f32 XA_B = C{ 0x0F }.c; // X active
  constexpr f32 YN_R = C{ 0x31 }.c; // Y normal
  constexpr f32 YN_G = C{ 0x7F }.c; // Y normal
  constexpr f32 YN_B = C{ 0x35 }.c; // Y normal
  constexpr f32 YH_R = C{ 0x31 }.c; // Y hovered
  constexpr f32 YH_G = C{ 0x8F }.c; // Y hovered
  constexpr f32 YH_B = C{ 0x35 }.c; // Y hovered
  constexpr f32 YA_R = C{ 0x41 }.c; // Y active
  constexpr f32 YA_G = C{ 0x7F }.c; // Y active
  constexpr f32 YA_B = C{ 0x35 }.c; // Y active
  constexpr f32 ZN_R = C{ 0x10 }.c; // Z normal
  constexpr f32 ZN_G = C{ 0x6E }.c; // Z normal
  constexpr f32 ZN_B = C{ 0xCB }.c; // Z normal
  constexpr f32 ZH_R = C{ 0x10 }.c; // Z hovered
  constexpr f32 ZH_G = C{ 0x7E }.c; // Z hovered
  constexpr f32 ZH_B = C{ 0xCB }.c; // Z hovered
  constexpr f32 ZA_R = C{ 0x10 }.c; // Z active
  constexpr f32 ZA_G = C{ 0x6E }.c; // Z active
  constexpr f32 ZA_B = C{ 0xDB }.c; // Z active

  void DrawVec3Control(const std::string& label, Vec3& values, float resetValue = 0.0f)
  {
    ImGui::PushID(label.c_str());

    constexpr float columnWidth = 100.0f;
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    const f32 line_height = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    constexpr auto HEIGHT_GAP = 3.0f;
    ImVec2 button_size{ line_height + HEIGHT_GAP, line_height };

    constexpr auto SPEED = 0.1f;

    {
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ XN_R, XN_G, XN_B, 1.0f });
      ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ XH_R, XH_G, XH_B, 1.0f });
      ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ XA_R, XA_G, XA_B, 1.0f });
      if (ImGui::Button("x", button_size))
        values.x = resetValue;
      ImGui::PopStyleColor(3);

      ImGui::SameLine();
      ImGui::DragFloat("##X", &values.x, SPEED);
      ImGui::PopItemWidth();
      ImGui::SameLine();
    }
    {
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ YN_R, YN_G, YN_B, 1.0f });
      ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ YH_R, YH_G, YH_B, 1.0f });
      ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ YA_R, YA_G, YA_B, 1.0f });
      if (ImGui::Button("y", button_size))
        values.y = resetValue;
      ImGui::PopStyleColor(3);

      ImGui::SameLine();
      ImGui::DragFloat("##Y", &values.y, SPEED);
      ImGui::PopItemWidth();
      ImGui::SameLine();
    }
    {
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ ZN_R, ZN_G, ZN_B, 1.0f });
      ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ ZH_R, ZH_G, ZH_B, 1.0f });
      ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ ZA_R, ZA_G, ZA_B, 1.0f });
      if (ImGui::Button("z", button_size))
        values.z = resetValue;
      ImGui::PopStyleColor(3);

      ImGui::SameLine();
      ImGui::DragFloat("##Z", &values.z, SPEED);
      ImGui::PopItemWidth();
    }
    ImGui::PopStyleVar();

    ImGui::Columns(1);

    ImGui::PopID();
  }
}

//--------------------------------------------------------------------------------------------------
SceneHierarchyPanel::SceneHierarchyPanel(const Ptr<Scene>& scene) : m_scene_context(scene) {}

void SceneHierarchyPanel::SetContext(const Ptr<Scene>& scene)
{
  m_scene_context = scene;

  { // TODO: Remove later
    m_selected_entity = Entity{ 2 };
  }
}

void SceneHierarchyPanel::OnImGuiRender()
{
  ImGui::Begin("Scene Entities");
  m_scene_context->EachEntity([&](Entity ent) { DrawEntityNode(ent); });

  if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
    m_selected_entity = std::nullopt;

  ImGui::End();

  ImGui::Begin("Entity Properties");
  DrawComponents(m_selected_entity);
  ImGui::End();
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
    constexpr auto OFFSET = 1434;
    bool expanded2 = ImGui::TreeNodeEx(TypeUtils::ToVoidPtr(OFFSET + i32(ent)),
                                       ImGuiTreeNodeFlags_None,
                                       "%s",
                                       tag.tag.c_str());
    if (expanded2)
      ImGui::TreePop();
    ImGui::TreePop();
  }
}

void SceneHierarchyPanel::DrawComponents(Opt<Entity> ent)
{
  if (m_scene_context->HasComponent<TagComponent>(ent))
    DrawTag(ent);

  if (m_scene_context->HasComponent<TransformComponent>(ent))
    DrawTransform(ent);

  if (m_scene_context->HasComponent<PrimitiveComponent>(ent))
    DrawPrimitive(ent);

  if (m_scene_context->HasComponent<CameraComponent>(ent))
  {
    DrawCamera(ent);
  }
}
void SceneHierarchyPanel::DrawCamera(Opt<Entity>& ent) const
{
  if (ImGui::TreeNodeEx(TypeUtils::ToVoidPtr(typeid(CameraComponent).hash_code()),
                        ImGuiTreeNodeFlags_DefaultOpen,
                        "CameraComponent"))
  {
    auto& comp = m_scene_context->GetComponent<CameraComponent>(ent.value());

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
void SceneHierarchyPanel::DrawPrimitive(Opt<Entity>& ent) const
{
  if (ImGui::TreeNodeEx(TypeUtils::ToVoidPtr(typeid(TransformComponent).hash_code()),
                        ImGuiTreeNodeFlags_DefaultOpen,
                        "Color"))
  {
    auto& cube_color = m_scene_context->GetComponent<PrimitiveComponent>(ent.value()).color;

    static Vec4 imgui_color{};
    imgui_color = cube_color.ToVec4();

    ImGui::ColorEdit4("Color", &imgui_color.x0);

    cube_color = Color(imgui_color);
    ImGui::TreePop();
  }
}
void SceneHierarchyPanel::DrawTransform(Opt<Entity>& ent) const
{
  if (ImGui::TreeNodeEx(TypeUtils::ToVoidPtr(typeid(TransformComponent).hash_code()),
                        ImGuiTreeNodeFlags_DefaultOpen,
                        "Transform"))
  {
    auto& pos = m_scene_context->GetComponent<TransformComponent>(ent.value()).position_values;
    auto& scale = m_scene_context->GetComponent<TransformComponent>(ent.value()).scale_values;
    auto& rotate = m_scene_context->GetComponent<TransformComponent>(ent.value()).rotate_values;

    DrawVec3Control("Position", pos);
    DrawVec3Control("Scale", scale, 1.0f);
    scale.x = Arithmetic::IsEqual(scale.x, 0.0f) ? 1.0f : scale.x;
    scale.y = Arithmetic::IsEqual(scale.y, 0.0f) ? 1.0f : scale.y;
    scale.z = Arithmetic::IsEqual(scale.z, 0.0f) ? 1.0f : scale.z;
    DrawVec3Control("Rotate", rotate);

    ImGui::TreePop();
  }
}
void SceneHierarchyPanel::DrawTag(Opt<Entity>& ent) const
{
  auto& tag = m_scene_context->GetComponent<TagComponent>(ent.value()).tag;

  constexpr auto BUFFER_SIZE = 256;
  std::array<char, BUFFER_SIZE> buffer{ '\0' };
  std::ranges::copy(tag, buffer.begin());
  if (ImGui::InputText("Tag", buffer.data(), sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
  {
    tag = std::string(buffer.data());
  }
}
