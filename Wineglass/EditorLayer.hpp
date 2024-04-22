#ifndef GRAPENGINE_EDITORLAYER_HPP
#define GRAPENGINE_EDITORLAYER_HPP

#include "grapengine.hpp"

#define FIRST_SCENE_TEST

namespace GE
{
  class EditorLayer : public Layer
  {
  public:
    EditorLayer();

    void OnAttach() override;

    void OnUpdate(TimeStep ts) override;

    void OnImGuiUpdate() override;

    void OnEvent(Event& ev) override;

  private:
#ifdef FIRST_SCENE_TEST
    Ref<Scene> m_scene;
    Entity m_camera_entity;

    Ref<Framebuffer> m_fb = nullptr;
    Dimension m_viewport_dimension{};
    //    bool m_viewport_focused{};
    bool m_viewport_hovered = true;
#else
    EditorCamera m_cam;
    Ref<WorldReference> m_world_ref = nullptr;
    Ref<Cube> m_light_1 = nullptr;
    Ref<Cube> m_light_2 = nullptr;
    Ref<Mesh> m_mesh = nullptr;

    Ref<PosAndTex2DShader> m_simple_shader = nullptr;
    Ref<MaterialShader> m_mat_shader = nullptr;

    Color m_ambient_color = Colors::WHITE;
    f32 m_ambient_str{ 1.0f };

    Vec3 m_light_pos_1{ 3.8f, 4.8f, 4.7f };
    Vec3 m_light_pos_2{ 3.8f, 4.8f, -4.7f };
    Color m_light_color_1{ 0xFFFFFFFF };
    Color m_light_color_2{ 0xFFFFFFFF };
    f32 m_light_strength{ 5.0f };

    Ref<Framebuffer> m_fb = nullptr;
    Vec2 m_viewport_size{};
    //    bool m_viewport_focused{};
    bool m_viewport_hovered = true;
#endif
  };
}

#endif // GRAPENGINE_EDITORLAYER_HPP
