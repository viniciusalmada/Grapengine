#include "renderer/ge_editor_camera.hpp"

#include <math/ge_vector.hpp>

using namespace GE;

struct EditorCamera::Impl
{
  float fov;
  float aspect_ratio;
  Mat4 projection_mat;
  Mat4 view_mat;
  float pitch_angle;
  float yaw_angle;
};

EditorCamera::EditorCamera(float fov, float aspectRatio) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->fov = fov;
  m_pimpl->aspect_ratio = aspectRatio;
}