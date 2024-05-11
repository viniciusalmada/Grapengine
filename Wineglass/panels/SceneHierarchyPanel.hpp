#ifndef GRAPENGINE_SCENEHIERARCHYPANEL_HPP
#define GRAPENGINE_SCENEHIERARCHYPANEL_HPP

#include "grapengine.hpp"

namespace GE
{

  class SceneHierarchyPanel
  {
  public:
    SceneHierarchyPanel(const Ref<Scene>& scene);

    void SetContext(const Ref<Scene>& scene);

    void OnImGuiRender();

  private:
    Ref<Scene> m_scene_context;
  };

} // GE

#endif // GRAPENGINE_SCENEHIERARCHYPANEL_HPP
