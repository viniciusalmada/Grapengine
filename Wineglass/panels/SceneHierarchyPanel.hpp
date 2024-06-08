#ifndef GRAPENGINE_SCENEHIERARCHYPANEL_HPP
#define GRAPENGINE_SCENEHIERARCHYPANEL_HPP

#include "grapengine.hpp"

namespace GE
{
  class SceneHierarchyPanel
  {
  public:
    SceneHierarchyPanel(const Ptr<Scene>& scene);

    void SetContext(const Ptr<Scene>& scene);

    void OnImGuiRender();

  private:
    void DrawEntityNode(Entity ent);
    void DrawComponents(Opt<Entity> ent);
    void DrawTag(Opt<Entity>& ent) const;
    void DrawTransform(Opt<Entity>& ent) const;
    void DrawPrimitive(Opt<Entity>& ent) const;
    void DrawCamera(Opt<Entity>& ent) const;

    Ptr<Scene> m_scene_context;
    Opt<Entity> m_selected_entity;
  };

} // GE

#endif // GRAPENGINE_SCENEHIERARCHYPANEL_HPP
