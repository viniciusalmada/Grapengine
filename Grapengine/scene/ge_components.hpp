#ifndef GRAPENGINE_GE_COMPONENTS_HPP
#define GRAPENGINE_GE_COMPONENTS_HPP

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
    Camera cam;
    bool active;

    CameraComponent() : cam(Camera{ Mat4{} }), active(false) {}
    CameraComponent(Mat4 proj, bool act) : cam(Camera{ proj }), active(act) {}
    CameraComponent(const CameraComponent& other) = default;
  };
}

#endif // GRAPENGINE_GE_COMPONENTS_HPP
