#include "Editor.hpp"

#include "EditorLayer.hpp"
#include "core/ge_entry_point.hpp"

GE::Editor::Editor() : Application("Wineglass - Grapengine", 1280, 720, "assets/ic_grapengine.png")
{
  GE_INFO("Create Wineglass Editor")
  auto editor_layer = MakeRef<EditorLayer>();
  Application::AddLayer(editor_layer);
}

GE::Ref<GE::Application> CreateApplication()
{
  return GE::MakeRef<GE::Editor>();
}