#ifndef GRAPENGINE_GE_COMPONENTS_HPP
#define GRAPENGINE_GE_COMPONENTS_HPP

#include "math/ge_vector.hpp"
#include "renderer/ge_editor_camera.hpp"
#include "renderer/ge_ishader_program.hpp"
#include "renderer/ge_vertex_array.hpp"

namespace GE::Component
{
  struct Transform
  {
    Mat4 model{};
  };

  struct Primitive
  {
    Ref<DrawingObject> drawing_obj{};
  };

  struct Material
  {
    Ref<IShaderProgram> shader;
  };

  struct ColorOnly
  {
    Ref<IShaderProgram> shader;
  };

  struct EditorCamera
  {
    Ref<::GE::EditorCamera> cam;
  };
}

#endif // GRAPENGINE_GE_COMPONENTS_HPP
