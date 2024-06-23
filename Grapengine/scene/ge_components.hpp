#ifndef GRAPENGINE_GE_COMPONENTS_HPP
#define GRAPENGINE_GE_COMPONENTS_HPP

#include "drawables/ge_color.hpp"
#include "drawables/ge_cube.hpp"
#include "ge_entity.hpp"
#include "ge_scene_camera.hpp"
#include "math/ge_transformations.hpp"
#include "math/ge_vector.hpp"
#include "renderer/ge_texture_2d.hpp"

namespace GE
{
  //----------------------------------------------------------------------------------------------
  class TagComponent
  {
  public:
    TagComponent(std::string&& t);

    [[nodiscard]] std::string& Tag() { return m_tag; }

    [[nodiscard]] const char* GetTag() const { return m_tag.c_str(); }

  private:
    std::string m_tag;
  };

  //----------------------------------------------------------------------------------------------
  class TransformComponent
  {
  public:
    TransformComponent(const Vec3& pos = Vec3{ 0, 0, 0 },
                       const Vec3& scale = Vec3{ 1, 1, 1 },
                       const Vec3& rotate = Vec3{ 0, 0, 0 }) :
        m_position_values(pos), m_scale_values(scale), m_rotate_values(rotate)
    {
    }
    TransformComponent(const TransformComponent& other) = default;
    TransformComponent& operator=(const TransformComponent& other) = default;
    [[nodiscard]] Mat4 GetModelMat() const
    {
      auto rotate = Transform::Rotate(m_rotate_values.x, { 1, 0, 0 }) *
                    Transform::Rotate(m_rotate_values.y, { 0, 1, 0 }) *
                    Transform::Rotate(m_rotate_values.z, { 0, 0, 1 });

      return Transform::Translate(m_position_values) * rotate * Transform::Scale(m_scale_values);
    }

    [[nodiscard]] Vec3& Position() { return m_position_values; }
    [[nodiscard]] Vec3& Scale() { return m_scale_values; }
    [[nodiscard]] Vec3& Rotate() { return m_rotate_values; }

  private:
    Vec3 m_position_values{ 0, 0, 0 };
    Vec3 m_scale_values{ 1, 1, 1 };
    Vec3 m_rotate_values{ 0, 0, 0 };
  };

  //----------------------------------------------------------------------------------------------
  class DrawingObject;
  class PrimitiveComponent
  {
  public:
    PrimitiveComponent(Ptr<Drawable> drawable, Color color = Colors::WHITE);

    [[nodiscard]] const Ptr<GE::Drawable>& GetDrawable() const { return m_drawable; }
    [[nodiscard]] const Color& GetColor() const { return m_color; }

    void SetColor(Color c) { m_color = c; }

  private:
    Ptr<Drawable> m_drawable;
    Color m_color;
  };

  //----------------------------------------------------------------------------------------------
  class CameraComponent
  {
  public:
    //    explicit CameraComponent();
    CameraComponent(const Vec3& eye, const Vec3& target, bool act, bool fixedRatio);

    [[nodiscard]] const SceneCamera& GetCamera() const { return m_camera; }
    [[nodiscard]] SceneCamera& GetCamera() { return m_camera; }
    [[nodiscard]] bool IsActive() const { return m_active; }
    [[nodiscard]] bool IsFixedRatio() const { return m_fixed_ratio; }

    void SetActive(bool active) { m_active = active; }

  private:
    SceneCamera m_camera;
    bool m_active;
    bool m_fixed_ratio;
  };

  //----------------------------------------------------------------------------------------------
  class ScriptableEntity;
  class Scene;
  class NativeScriptComponent
  {
  public:
    explicit NativeScriptComponent();

    template <typename T>
    void Bind()
    {
      m_instantiate_fun = [this](Entity e, Scene& s) { m_instance = new T(e, std::ref(s)); };
      m_destroy_fun = [this]()
      {
        delete static_cast<T*>(m_instance);
        m_instance = nullptr;
      };
    }

    [[nodiscard]] bool IsValid() const { return m_instance != nullptr; }
    void Instantiate(Entity ent, Scene& scene) const { m_instantiate_fun(ent, scene); }
    [[nodiscard]] ScriptableEntity* GetInstance() const { return m_instance; }

  private:
    ScriptableEntity* m_instance;
    std::function<void(Entity, Scene&)> m_instantiate_fun;
    std::function<void()> m_destroy_fun;
  };

  //----------------------------------------------------------------------------------------------
  class AmbientLightComponent
  {
  public:
    AmbientLightComponent(Color c, f32 str);

    [[nodiscard]] bool IsActive() const { return m_active; }
    [[nodiscard]] const Color& GetColor() const { return m_color; }
    [[nodiscard]] f32 GetStr() const { return m_strenght; }

    void SetActive(bool active) { m_active = active; }
    void SetColor(Color c) { m_color = c; }
    void SetStr(f32 s) { m_strenght = s; }

  private:
    Color m_color;
    f32 m_strenght;
    bool m_active;
  };

  //----------------------------------------------------------------------------------------------
  class LightSpotComponent
  {
  public:
    LightSpotComponent(Color c, Vec3 pos, f32 str, bool active);

    [[nodiscard]] Color& ColorRef() { return m_color; }
    [[nodiscard]] Vec3& Position() { return m_position; }
    [[nodiscard]] f32& Strenght() { return m_strenght; }
    [[nodiscard]] bool& Active() { return m_active; }

    [[nodiscard]] const Color& GetColor() const { return m_color; }
    [[nodiscard]] const Vec3& GetPos() const { return m_position; }
    [[nodiscard]] f32 GetStr() const { return m_strenght; }
    [[nodiscard]] bool IsActive() const { return m_active; }
    [[nodiscard]] const Ptr<GE::Drawable>& GetDrawable() const { return m_drawable; }

  private:
    Color m_color;
    Vec3 m_position;
    f32 m_strenght;
    bool m_active;
    Ptr<Drawable> m_drawable;
  };

  //----------------------------------------------------------------------------------------------
  using VarComponent = std::variant< //
    TagComponent,
    TransformComponent,
    PrimitiveComponent,
    CameraComponent,
    NativeScriptComponent,
    AmbientLightComponent,
    LightSpotComponent //
    >;
}

#endif // GRAPENGINE_GE_COMPONENTS_HPP
