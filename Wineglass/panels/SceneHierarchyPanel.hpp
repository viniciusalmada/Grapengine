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
    void DrawComponents(Entity ent);

    void DrawTag(Entity ent) const;
    void DrawTransform(Entity ent) const;
    void DrawPrimitive(Entity ent) const;
    void DrawCamera(Entity ent) const;
    void DrawAmbientLight(Entity ent) const;
    void DrawLights(Entity ent) const;

    Ptr<Scene> m_scene_context;
    Opt<Entity> m_selected_entity;
  };

} // GE

#endif // GRAPENGINE_SCENEHIERARCHYPANEL_HPP
