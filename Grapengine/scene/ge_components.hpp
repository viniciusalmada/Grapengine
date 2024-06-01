#ifndef GRAPENGINE_GE_COMPONENTS_HPP
#define GRAPENGINE_GE_COMPONENTS_HPP

#include "drawables/ge_color.hpp"
#include "drawables/ge_cube.hpp"
#include "ge_comp_types.hpp"
#include "ge_entity.hpp"
#include "ge_scene_camera.hpp"
#include "math/ge_transformations.hpp"
#include "math/ge_vector.hpp"
#include "renderer/ge_ishader_program.hpp"

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

    TagComponent(const char* t);
  };

  struct TransformComponent : public BaseComponent
  {
    Mat4 transform;
    [[nodiscard]] CompType Type() const final;
    TransformComponent(const Mat4& transf);
  };

  struct TranslateScaleComponent : public BaseComponent
  {
    Vec3 position_values;
    Vec3 scale_values;
    [[nodiscard]] CompType Type() const final;
    TranslateScaleComponent(const Vec3& pos, const Vec3& scale);
    [[nodiscard]] Mat4 GetModelMat() const
    {
      return Transform::Translate(position_values) * Transform::Scale(scale_values);
    }
  };

  class DrawingObject;
  struct PrimitiveComponent : public BaseComponent
  {
    Ptr<DrawingObject> drawing_obj;
    PrimitiveComponent(const Ptr<DrawingObject>& drawObj);
    PrimitiveComponent(const PrimitiveComponent&);
    [[nodiscard]] CompType Type() const final;
  };

  struct CubeComponent : public BaseComponent
  {
    Cube cube;
    CubeComponent(Color color);
    CompType Type() const override;
  };

  struct MaterialComponent : public BaseComponent
  {
    Ptr<MaterialShader> shader;
    MaterialComponent(Ptr<MaterialShader> shader);
    [[nodiscard]] CompType Type() const final;
  };

  struct ColorOnlyComponent : public BaseComponent
  {
    Ptr<PosAndTex2DShader> shader;
    [[nodiscard]] CompType Type() const final;
    ColorOnlyComponent(Ptr<PosAndTex2DShader> s);
    ColorOnlyComponent(const ColorOnlyComponent&);
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
}

#endif // GRAPENGINE_GE_COMPONENTS_HPP
