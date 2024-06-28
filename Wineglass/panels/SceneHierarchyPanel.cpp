#include "SceneHierarchyPanel.hpp"

#include "imgui.h"

#include <imgui_internal.h>

using namespace std::string_literals;
using namespace GE;

namespace
{
  constexpr Color X_NORMAL{ 0xB20F0FFF };
  constexpr Color X_HOVERED{ 0xC20F0FFF };
  constexpr Color X_ACTIVE{ 0xB21F0FFF };
  constexpr Color Y_NORMAL{ 0x317F35FF };
  constexpr Color Y_HOVERED{ 0x318F35FF };
  constexpr Color Y_ACTIVE{ 0x417F35FF };
  constexpr Color Z_NORMAL{ 0x106ECBFF };
  constexpr Color Z_HOVERED{ 0x107ECBFF };
  constexpr Color Z_ACTIVE{ 0x106EDBFF };

  //-------------------------------------------------------------------------------------------------
  void DrawVec3Control(const std::string& label, Vec3& values, float resetValue = 0.0f)
  {
    auto* const BOLD_FONT = ImGui::GetIO().Fonts->Fonts[1];

    ImGui::PushID(label.c_str());

    constexpr float columnWidth = 65.0f;
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    const f32 line_height = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    constexpr auto HEIGHT_GAP = 1.0f;
    const ImVec2 button_size{ line_height + HEIGHT_GAP, line_height };

    constexpr auto SPEED = 0.1f;

    {
      ImGui::PushStyleColor(ImGuiCol_Button, X_NORMAL.ToVec4<ImVec4>());
      ImGui::PushStyleColor(ImGuiCol_ButtonHovered, X_HOVERED.ToVec4<ImVec4>());
      ImGui::PushStyleColor(ImGuiCol_ButtonActive, X_ACTIVE.ToVec4<ImVec4>());
      ImGui::PushFont(BOLD_FONT);
      if (ImGui::Button("x", button_size))
        values.x = resetValue;
      ImGui::PopFont();
      ImGui::PopStyleColor(3);

      ImGui::SameLine();
      ImGui::DragFloat("##X", &values.x, SPEED, 0, 0, "%2.2f");
      ImGui::PopItemWidth();
      ImGui::SameLine();
    }
    {
      ImGui::PushStyleColor(ImGuiCol_Button, Y_NORMAL.ToVec4<ImVec4>());
      ImGui::PushStyleColor(ImGuiCol_ButtonHovered, Y_HOVERED.ToVec4<ImVec4>());
      ImGui::PushStyleColor(ImGuiCol_ButtonActive, Y_ACTIVE.ToVec4<ImVec4>());
      ImGui::PushFont(BOLD_FONT);
      if (ImGui::Button("y", button_size))
        values.y = resetValue;
      ImGui::PopFont();
      ImGui::PopStyleColor(3);

      ImGui::SameLine();
      ImGui::DragFloat("##Y", &values.y, SPEED, 0, 0, "%2.2f");
      ImGui::PopItemWidth();
      ImGui::SameLine();
    }
    {
      ImGui::PushStyleColor(ImGuiCol_Button, Z_NORMAL.ToVec4<ImVec4>());
      ImGui::PushStyleColor(ImGuiCol_ButtonHovered, Z_HOVERED.ToVec4<ImVec4>());
      ImGui::PushStyleColor(ImGuiCol_ButtonActive, Z_ACTIVE.ToVec4<ImVec4>());
      ImGui::PushFont(BOLD_FONT);
      if (ImGui::Button("z", button_size))
        values.z = resetValue;
      ImGui::PopFont();
      ImGui::PopStyleColor(3);

      ImGui::SameLine();
      ImGui::DragFloat("##Z", &values.z, SPEED, 0, 0, "%2.2f");
      ImGui::PopItemWidth();
    }
    ImGui::PopStyleVar();

    ImGui::Columns(1);

    ImGui::PopID();
  }

  //  const int flags = is_selected | ImGuiTreeNodeFlags_OpenOnArrow |
  //  ImGuiTreeNodeFlags_SpanFullWidth;
  constexpr ImGuiTreeNodeFlags TREE_NODE_FLAGS =
    ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen //
    | ImGuiTreeNodeFlags_AllowOverlap | ImGuiTreeNodeFlags_SpanFullWidth;

  //-------------------------------------------------------------------------------------------------
  template <typename T, typename UIFun>
  void DrawComponent(const std::string&& name, Scene& scene, Entity ent, const UIFun&& fun)
  {
    if (!scene.HasComponent<T>(ent))
      return;
    constexpr auto FRAME_PADDING = ImVec2{ 4, 4 };
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, FRAME_PADDING);
    bool open = ImGui::TreeNodeEx(TypeUtils::ToVoidPtr(typeid(T).hash_code()),
                                  TREE_NODE_FLAGS,
                                  "%s",
                                  name.c_str());
    constexpr auto X_OFFSET = 25.0f;
    ImGui::SameLine(ImGui::GetWindowWidth() - X_OFFSET);
    constexpr auto BUTTON_SIZE = ImVec2{ 20, 20 };
    constexpr auto SETTINGS_ID = "ComponentSettings";
    if (ImGui::Button("+", BUTTON_SIZE))
    {
      ImGui::OpenPopup(SETTINGS_ID);
    }
    ImGui::PopStyleVar();

    bool remove_comp = false;
    if (ImGui::BeginPopup(SETTINGS_ID))
    {
      if (ImGui::MenuItem("Remove commponent"))
        remove_comp = true;

      ImGui::EndPopup();
    }

    if (open)
    {
      fun(scene, ent, std::ref(scene.GetComponent<T>(ent)));
      ImGui::TreePop();
    }

    if (remove_comp)
      scene.RemoveComponent<T>(ent);
  }

  //-------------------------------------------------------------------------------------------------
  void DrawCamera(Scene& scene, Entity e, CameraComponent& comp)
  {
    if (!comp.IsActive())
    {
      if (ImGui::Button("Activate camera"))
      {
        comp.SetActive(true);
        scene.UpdateActiveCamera(e);
      }
    }
    bool is_fixed = comp.IsFixedRatio();
    ImGui::Checkbox("Fixed AR", &is_fixed);

    const std::array TITLES{ "Perspective"s, "Orthographic"s };
    auto current_mode = comp.GetCamera().GetProjectionMode();
    const char* preview_value = TITLES.at(static_cast<u8>(current_mode)).c_str();
    if (ImGui::BeginCombo("Projection", preview_value))
    {
      for (u32 n = 0; n < TITLES.size(); n++)
      {
        const bool is_selected = (static_cast<u8>(current_mode) == n);
        if (ImGui::Selectable(TITLES.at(n).c_str(), is_selected))
        {
          current_mode = static_cast<ProjectionMode>(n);
          comp.GetCamera().SetProjectionMode(current_mode);
        }

        if (is_selected)
          ImGui::SetItemDefaultFocus();
      }
      ImGui::EndCombo();
    }

    if (comp.GetCamera().IsInProjectionMode(ProjectionMode::PERSPECTIVE))
    {
      f32 fov = comp.GetCamera().GetFov();
      if (ImGui::DragFloat("FOV",
                           &fov,
                           1.0f,
                           15.0f,
                           100.0f,
                           "%1.0f deg",
                           ImGuiSliderFlags_AlwaysClamp))
        comp.GetCamera().SetFov(fov);
    }

    if (comp.GetCamera().IsInProjectionMode(ProjectionMode::ORTHO))
    {
      f32 size = comp.GetCamera().GetOrthographicSize();
      if (ImGui::DragFloat("Size",
                           &size,
                           10.0f,
                           5.0f,
                           100.0f,
                           "%1.0f",
                           ImGuiSliderFlags_AlwaysClamp))
        comp.GetCamera().SetOrthographicSize(size);
    }

    Vec3 eye = comp.GetCamera().GetPosition();
    Vec3 target = comp.GetCamera().GetTarget();

    constexpr auto CAMERA_STEP = 0.01f;
    bool changed_eye = ImGui::DragFloat3("Eye", &eye.x, CAMERA_STEP);
    bool changed_target = ImGui::DragFloat3("Target", &target.x, CAMERA_STEP);

    if (changed_eye || changed_target)
      comp.GetCamera().SetView(eye, target);
  }

  //-------------------------------------------------------------------------------------------------
  void DrawPrimitive(Scene& /*scene*/, Entity /*e*/, PrimitiveComponent& comp)
  {
    static Vec4 imgui_color{};
    imgui_color = comp.GetColor().ToVec4();

    ImGui::ColorEdit4("Color", &imgui_color.x0);

    comp.SetColor(Color(imgui_color));
  }

  //-------------------------------------------------------------------------------------------------
  void DrawTransform(Scene& /*scene*/, Entity /*e*/, TransformComponent& comp)
  {
    auto& pos = comp.Position();
    auto& scale = comp.Scale();
    auto& rotate = comp.Rotate();

    DrawVec3Control("Position", pos);
    DrawVec3Control("Scale", scale, 1.0f);
    scale.x = Arithmetic::IsEqual(scale.x, 0.0f) ? 1.0f : scale.x;
    scale.y = Arithmetic::IsEqual(scale.y, 0.0f) ? 1.0f : scale.y;
    scale.z = Arithmetic::IsEqual(scale.z, 0.0f) ? 1.0f : scale.z;
    DrawVec3Control("Rotate", rotate);
  }

  //-------------------------------------------------------------------------------------------------
  void DrawAmbientLight(Scene& /*scene*/, Entity /*e*/, AmbientLightComponent& comp)
  {
    static Vec4 imgui_color{};
    imgui_color = comp.GetColor().ToVec4();
    ImGui::ColorEdit4("Color", &imgui_color.x0);
    comp.SetColor(Color(imgui_color));

    f32 str = comp.GetStr();
    constexpr auto STRENGHT_STEP = 0.01f;
    ImGui::DragFloat("Strenght", &str, STRENGHT_STEP, 0.0f, 1.0f);
    comp.SetStr(str);
  }

  //-------------------------------------------------------------------------------------------------
  void DrawLights(Scene& /*scene*/, Entity /*e*/, LightSpotComponent& comp)
  {
    static Vec4 imgui_color{};
    imgui_color = comp.ColorRef().ToVec4();
    ImGui::ColorEdit4("Color", &imgui_color.x0);
    comp.ColorRef() = Color(imgui_color);

    DrawVec3Control("Position", comp.Position(), 0.0f);

    constexpr auto LIGHT_STEP = 0.1f;
    constexpr auto MIN_LIGHT_STR = 0.0f;
    constexpr auto MAX_LIGHT_STR = 10.0f;
    ImGui::DragFloat("Strenght", &comp.Strenght(), LIGHT_STEP, MIN_LIGHT_STR, MAX_LIGHT_STR);

    ImGui::Checkbox("Active", &comp.Active());
  }

}

//--------------------------------------------------------------------------------------------------
SceneHierarchyPanel::SceneHierarchyPanel(const Ptr<Scene>& scene) : m_scene_context(*scene)
{
  { // TODO: Remove later
    m_selected_entity = Entity{ 2 };
  }
}

//-------------------------------------------------------------------------------------------------
void SceneHierarchyPanel::OnImGuiRender()
{
  ImGui::Begin("Scene Entities");

  m_scene_context.EachEntity([&](Entity ent) { DrawEntityNode(ent); });

  if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
    m_selected_entity = std::nullopt;

  if (!m_selected_entity)
  {
    if (ImGui::BeginPopupContextWindow())
    {
      if (ImGui::MenuItem("Create empty Entity"))
        m_scene_context.CreateEntity("Empty entity");

      ImGui::EndPopup();
    }
  }

  ImGui::End();

  ImGui::Begin("Entity Properties");
  if (m_selected_entity)
  {
    [&](Entity ent)
    {
      DrawComponents(ent);
      constexpr auto ADD_COMP_ID = "AddComponent";
      if (ImGui::Button("Add component"))
        ImGui::OpenPopup(ADD_COMP_ID);

      if (ImGui::BeginPopup(ADD_COMP_ID))
      {
        if (!m_scene_context.HasComponent<CameraComponent>(ent))
        {
          if (ImGui::MenuItem("Camera"))
          {
            m_scene_context.AddComponent<CameraComponent>(ent, Vec3{}, Vec3{}, false, true);
            ImGui::CloseCurrentPopup();
          }
        }

        if (!m_scene_context.HasComponent<PrimitiveComponent>(ent))
        {
          if (ImGui::MenuItem("Cube primitive"))
          {
            m_scene_context.AddComponent<PrimitiveComponent>(ent,
                                                             Cube::Make(),
                                                             Colors::RandomColor());
            m_scene_context.AddComponent<TransformComponent>(ent);
            ImGui::CloseCurrentPopup();
          }
        }

        ImGui::EndPopup();
      }
    }(m_selected_entity.value());
  }
  ImGui::End();
}

//-------------------------------------------------------------------------------------------------
void SceneHierarchyPanel::DrawEntityNode(Entity ent)
{
  auto& tag = m_scene_context.GetComponent<TagComponent>(ent);
  if (ImGui::Selectable(tag.GetTag(), ent == m_selected_entity))
  {
    m_selected_entity = ent;
  }

  bool delete_entity = false;
  if (m_selected_entity == ent)
  {
    if (ImGui::BeginPopupContextWindow())
    {
      if (ImGui::MenuItem("Delete entity"))
        delete_entity = true;
      ImGui::EndPopup();
    }
  }

  if (delete_entity)
  {
    m_scene_context.DestroyEntity(ent);
    if (ent == m_selected_entity)
      m_selected_entity = {};
  }

  //  void* node_id = TypeUtils::ToVoidPtr(i32(ent));
  //  const int is_selected = ent == m_selected_entity ? ImGuiTreeNodeFlags_Selected : 0;
  //
  //  auto& tag = m_scene_context.GetComponent<TagComponent>(ent);
  //  bool expanded = ImGui::TreeNodeEx(node_id, TREE_NODE_FLAGS, "%s", tag.GetTag());
  //
  //  if (ImGui::IsItemClicked(ImGuiMouseButton_Left) ||
  //  ImGui::IsItemClicked(ImGuiMouseButton_Right))
  //  {
  //    m_selected_entity = ent;
  //  }
  //
  //  bool delete_entity = false;
  //  if (m_selected_entity == ent)
  //  {
  //    if (ImGui::BeginPopupContextWindow())
  //    {
  //      if (ImGui::MenuItem("Delete entity"))
  //        delete_entity = true;
  //      ImGui::EndPopup();
  //    }
  //  }
  //
  //  if (delete_entity)
  //  {
  //    m_scene_context.DestroyEntity(ent);
  //    if (ent == m_selected_entity)
  //      m_selected_entity = {};
  //  }
}

//-------------------------------------------------------------------------------------------------
void SceneHierarchyPanel::DrawComponents(Entity ent)
{
  if (m_scene_context.HasComponent<TagComponent>(ent))
    DrawTag(ent);

  DrawComponent<TransformComponent>("Transform", m_scene_context, ent, DrawTransform);
  DrawComponent<PrimitiveComponent>("Primitive", m_scene_context, ent, DrawPrimitive);
  DrawComponent<CameraComponent>("Camera", m_scene_context, ent, DrawCamera);
  DrawComponent<AmbientLightComponent>("Ambient Light", m_scene_context, ent, DrawAmbientLight);
  DrawComponent<LightSpotComponent>("Light Spots", m_scene_context, ent, DrawLights);
}

//-------------------------------------------------------------------------------------------------
void SceneHierarchyPanel::DrawTag(Entity ent) const
{
  auto& tag = m_scene_context.GetComponent<TagComponent>(ent).Tag();

  constexpr auto BUFFER_SIZE = 256;
  std::array<char, BUFFER_SIZE> buffer{ '\0' };
  std::ranges::copy(tag, buffer.begin());
  if (ImGui::InputText("Tag", buffer.data(), sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
  {
    tag = std::string(buffer.data());
  }
}
