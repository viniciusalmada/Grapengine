#ifndef GRAPENGINE_GE_COMPONENTS_HPP
#define GRAPENGINE_GE_COMPONENTS_HPP

#include "ge_scene_camera.hpp"
#include "ge_scriptable_entity.hpp"
#include "math/ge_vector.hpp"
#include "renderer/ge_camera.hpp"
#include "renderer/ge_ishader_program.hpp"
#include "renderer/ge_vertex_array.hpp"

namespace GE
{
  struct TagComponent
  {
    std::string_view tag;
  };

  struct TransformComponent
  {
    Mat4 transform;
  };

  struct PrimitiveComponent
  {
    Ref<DrawingObject> drawing_obj;
  };

  struct MaterialComponent
  {
    Ref<IShaderProgram> shader;
  };

  struct ColorOnlyComponent
  {
    Ref<IShaderProgram> shader;
  };

  struct CameraComponent
  {
    SceneCamera camera;
    bool active;
    bool fixed_ratio;

    CameraComponent() : active(false), fixed_ratio(false) {}
    CameraComponent(bool act, bool fixedRatio) : active(act), fixed_ratio(fixedRatio) {}
    CameraComponent(const CameraComponent& other) = default;
  };

  struct NativeScriptComponent
  {
    ScriptableEntity* instance;

    std::function<void(Entity, Scene&)> instantiateFun;
    std::function<void()> destroyFun;

    std::function<void(ScriptableEntity*)> onCreateFun;
    std::function<void(ScriptableEntity*)> onDestroyFun;
    std::function<void(ScriptableEntity*, TimeStep)> onUpdateFun;

    template <typename T, typename... Args>
    void Bind()
    {
      instantiateFun = [this](Entity e, Scene& s) { instance = new T(e, std::ref(s)); };
      destroyFun = [this]()
      {
        delete (T*)instance;
        instance = nullptr;
      };
      onCreateFun = [](ScriptableEntity* ent) { ((T*)ent)->OnCreate(); };
      onDestroyFun = [](ScriptableEntity* ent) { ((T*)ent)->OnDestroy(); };
      onUpdateFun = [](ScriptableEntity* ent, TimeStep ts) { ((T*)ent)->OnUpdate(ts); };
    }
  };
}

#endif // GRAPENGINE_GE_COMPONENTS_HPP
