#ifndef GRAPENGINE_GE_COMPONENTS_HPP
#define GRAPENGINE_GE_COMPONENTS_HPP

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
    virtual ~BaseComponent() = default;
    [[nodiscard]] virtual CompType Type() const { return CompType::BASE; };
  };

  struct TagComponent final : public BaseComponent
  {
    std::string tag;
    [[nodiscard]] CompType Type() const final { return CompType::TAG; }

    TagComponent(const char* t) : tag(t) {}
  };

  struct TransformComponent : public BaseComponent
  {
    Mat4 transform;
    [[nodiscard]] CompType Type() const final { return CompType::TRANF; }
    TransformComponent(const Mat4& transf) : transform(transf) {}
  };

  struct TranslateScaleComponent : public BaseComponent
  {
    Vec3 position_values;
    Vec3 scale_values;
    [[nodiscard]] CompType Type() const final { return CompType::TRANSL_SCALE; }
    TranslateScaleComponent(const Vec3& pos, const Vec3& scale) :
        position_values(pos), scale_values(scale)
    {
    }
    [[nodiscard]] Mat4 GetModelMat() const
    {
      return Transform::Translate(position_values) * Transform::Scale(scale_values);
    }
  };

  class DrawingObject;
  struct PrimitiveComponent : public BaseComponent
  {
    Ref<DrawingObject> drawing_obj;
    PrimitiveComponent(const Ref<DrawingObject>& drawObj) : drawing_obj(drawObj) {}
    [[nodiscard]] CompType Type() const final { return CompType::PRIMITIVE; }
  };

  struct MaterialComponent : public BaseComponent
  {
    Ref<IShaderProgram> shader;
    [[nodiscard]] CompType Type() const final { return CompType::MATERIAL; }
  };

  struct ColorOnlyComponent : public BaseComponent
  {
    Ref<IShaderProgram> shader;
    [[nodiscard]] CompType Type() const final { return CompType::COLOR_ONLY; }
    ColorOnlyComponent(Ref<IShaderProgram> s) : shader(std::move(s)) {}
  };

  struct CameraComponent : public BaseComponent
  {
    SceneCamera camera;
    bool active;
    bool fixed_ratio;

    [[nodiscard]] CompType Type() const final { return CompType::CAMERA; }
    CameraComponent(const Vec3& eye, const Vec3& target, bool act, bool fixedRatio) :
        active(act), fixed_ratio(fixedRatio)
    {
      camera.SetView(eye, target);
    }
  };

  class ScriptableEntity;
  class Scene;
  struct NativeScriptComponent : public BaseComponent
  {
    ScriptableEntity* instance;

    std::function<void(Entity, Scene&)> instantiateFun;
    std::function<void()> destroyFun;

    explicit NativeScriptComponent() : instance(nullptr), instantiateFun({}), destroyFun({}) {}

    [[nodiscard]] CompType Type() const final { return CompType::NATIVE_SCRIPT; }
    template <typename T>
    void Bind()
    {
      instantiateFun = [this](Entity e, Scene& s) { instance = new T(e, std::ref(s)); };
      destroyFun = [this]()
      {
        delete (T*)instance;
        instance = nullptr;
      };
    }
  };
}

#endif // GRAPENGINE_GE_COMPONENTS_HPP
