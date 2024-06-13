#ifndef GRAPENGINE_GE_COMPONENTS_HPP
#define GRAPENGINE_GE_COMPONENTS_HPP

#include "drawables/ge_color.hpp"
#include "drawables/ge_cube.hpp"
#include "ge_comp_types.hpp"
#include "ge_entity.hpp"
#include "ge_scene_camera.hpp"
#include "math/ge_transformations.hpp"
#include "math/ge_vector.hpp"
#include "renderer/ge_texture_2d.hpp"
#include "renderer/ge_vertices_data.hpp"
#include "renderer/shader_programs/ge_material_shader.hpp"
#include "renderer/shader_programs/ge_pos_tex_shader.hpp"

namespace GE
{
  struct BaseComponent
  {
    BaseComponent() = default;
    BaseComponent(const BaseComponent&) = delete;
    virtual ~BaseComponent();
    [[nodiscard]] virtual CompType Type() const;
  };

  struct TagComponent final : public BaseComponent
  {
    std::string tag;
    [[nodiscard]] CompType Type() const final;

    TagComponent(std::string&& t);
  };

  struct TransformComponent : public BaseComponent
  {
    Vec3 rotate_values{ 0, 0, 0 };
    Vec3 position_values{ 0, 0, 0 };
    Vec3 scale_values{ 1, 1, 1 };
    [[nodiscard]] CompType Type() const final;
    TransformComponent(const Vec3& pos = Vec3{ 0, 0, 0 },
                       const Vec3& scale = Vec3{ 1, 1, 1 },
                       const Vec3& rotate = Vec3{ 0, 0, 0 });
    [[nodiscard]] Mat4 GetModelMat() const
    {
      auto rotate = Transform::Rotate(rotate_values.x, { 1, 0, 0 }) *
                    Transform::Rotate(rotate_values.y, { 0, 1, 0 }) *
                    Transform::Rotate(rotate_values.z, { 0, 0, 1 });

      return Transform::Translate(position_values) * rotate * Transform::Scale(scale_values);
    }
  };

  class DrawingObject;
  struct PrimitiveComponent : public BaseComponent
  {
    Ptr<Drawable> drawable;
    Color color;
    PrimitiveComponent(Ptr<Drawable> drawable, Color color = Colors::WHITE);
    PrimitiveComponent(const PrimitiveComponent&);
    CompType Type() const override;
  };

  struct CameraComponent : public BaseComponent
  {
    SceneCamera camera;
    bool active;
    bool fixed_ratio;

    [[nodiscard]] CompType Type() const final;
    CameraComponent(const Vec3& eye, const Vec3& target, bool act, bool fixedRatio);
  };

  class ScriptableEntity;
  class Scene;
  struct NativeScriptComponent : public BaseComponent
  {
    ScriptableEntity* instance;

    std::function<void(Entity, Scene&)> instantiateFun;
    std::function<void()> destroyFun;

    explicit NativeScriptComponent();

    [[nodiscard]] CompType Type() const final;
    template <typename T>
    void Bind()
    {
      instantiateFun = [this](Entity e, Scene& s) { instance = new T(e, std::ref(s)); };
      destroyFun = [this]()
      {
        delete static_cast<T*>(instance);
        instance = nullptr;
      };
    }
  };

  struct AmbientLightComponent final : public BaseComponent
  {
    Color color;
    f32 strenght;
    bool active;

    AmbientLightComponent(Color c = Colors::WHITE, f32 str = 1.0f);

    ~AmbientLightComponent() override;
    [[nodiscard]] CompType Type() const override;
  };

  struct LightSpotComponent final : public BaseComponent
  {
    Color color;
    Vec3 position;
    f32 strenght;
    bool active;
    Ptr<Drawable> drawable;

    LightSpotComponent(Color c = Colors::WHITE,
                       Vec3 pos = { 0, 0, 0 },
                       f32 str = 1.0f,
                       bool active = true);

    ~LightSpotComponent() override;
    [[nodiscard]] CompType Type() const override;
  };
}

#endif // GRAPENGINE_GE_COMPONENTS_HPP
