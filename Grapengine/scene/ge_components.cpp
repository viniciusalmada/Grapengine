#include "ge_components.hpp"

using namespace GE;

//----------------------------------------------------------------------------------------------
TagComponent::TagComponent(std::string&& t) : m_tag(std::move(t)) {}

//----------------------------------------------------------------------------------------------
PrimitiveComponent::PrimitiveComponent(const Drawable& dra, Color c) : m_drawable(dra), m_color(c)
{
}
const Drawable& PrimitiveComponent::GetDrawable() const
{
  return m_drawable;
}
Drawable& PrimitiveComponent::GetDrawable()
{
  return m_drawable;
}
const Color& PrimitiveComponent::GetColor() const
{
  return m_color;
}
void PrimitiveComponent::SetColor(Color c)
{
  m_color = c;
}

//----------------------------------------------------------------------------------------------
CameraComponent::CameraComponent(const Vec3& eye, const Vec3& target, bool act, bool fixedRatio) :
    m_active(act), m_fixed_ratio(fixedRatio)
{
  m_camera.SetView(eye, target);
}

//----------------------------------------------------------------------------------------------
NativeScriptComponent::NativeScriptComponent() :
    m_instance(nullptr), m_instantiate_fun({}), m_destroy_fun({})
{
}

//----------------------------------------------------------------------------------------------
AmbientLightComponent::AmbientLightComponent(Color c, f32 str) :
    m_color(c), m_strenght(str), m_active(true)
{
}

//----------------------------------------------------------------------------------------------
LightSourceComponent::LightSourceComponent(Color c, Vec3 pos, f32 str, bool act) :
    m_color(c), m_position(pos), m_strenght(str), m_active(act), m_drawable(Cube().GetDrawable())
{
}
