#ifndef GRAPENGINE_SCENEHIERARCHYPANEL_HPP
#define GRAPENGINE_SCENEHIERARCHYPANEL_HPP

#include "grapengine.hpp"

namespace GE
{
  class SceneHierarchyPanel
  {
  public:
    SceneHierarchyPanel(const Ptr<Scene>& scene);
    SceneHierarchyPanel(const SceneHierarchyPanel&) = delete;
    SceneHierarchyPanel(SceneHierarchyPanel&&) = delete;
    SceneHierarchyPanel& operator=(const SceneHierarchyPanel&) = delete;
    SceneHierarchyPanel& operator=(SceneHierarchyPanel&&) = delete;

    void OnImGuiRender();

  private:
    void DrawEntityNode(Entity ent);
    void DrawComponents(Entity ent);

    void DrawTag(Entity ent) const;

    Scene& m_scene_context;
    Opt<Entity> m_selected_entity;
  };

} // GE

#endif // GRAPENGINE_SCENEHIERARCHYPANEL_HPP
