#ifndef GRAPENGINE_GE_COMPONENTS_HPP
#define GRAPENGINE_GE_COMPONENTS_HPP

#include "math/ge_vector.hpp"
#include "renderer/ge_editor_camera.hpp"
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
    Mat4 model{};
  };

  struct PrimitiveComponent
  {
    Ref<DrawingObject> drawing_obj{};
  };

  struct MaterialComponent
  {
    Ref<IShaderProgram> shader;
  };

  struct ColorOnlyComponent
  {
    Ref<IShaderProgram> shader;
  };

  struct EditorCameraComponent
  {
    Ref<::GE::EditorCamera> cam;
  };
}

#endif // GRAPENGINE_GE_COMPONENTS_HPP
