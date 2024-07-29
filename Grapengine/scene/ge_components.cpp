#include "ge_components.hpp"

#include "math/ge_arithmetic.hpp"

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
CameraComponent::CameraComponent(const SceneCamera& cam, bool isActive, bool isFixedRatio) :
    m_camera(cam), m_active(isActive), m_fixed_ratio(isFixedRatio)
{
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
AmbientLightComponent::AmbientLightComponent(Color c, f32 str) : AmbientLightComponent(c, str, true)
{
}

AmbientLightComponent::AmbientLightComponent(Color c, f32 str, bool active) :
    m_color(c), m_strenght(str), m_active(active)
{
}

bool AmbientLightComponent::operator==(const AmbientLightComponent& lhs) const
{
  return Arithmetic::IsEqual(m_strenght, lhs.m_strenght) && //
         m_active == lhs.m_active &&                        //
         m_color == lhs.m_color;
}
//----------------------------------------------------------------------------------------------
LightSourceComponent::LightSourceComponent(Color c, Vec3 pos, f32 str, bool act) :
    m_color(c), m_position(pos), m_strenght(str), m_active(act), m_drawable(Cube().GetDrawable())
{
}

bool LightSourceComponent::operator==(const LightSourceComponent& rhs) const
{
  return m_color == rhs.m_color &&                          //
         m_position == rhs.m_position &&                    //
         Arithmetic::IsEqual(m_strenght, rhs.m_strenght) && //
         m_active == rhs.m_active &&                        //
         m_drawable == rhs.m_drawable;
}
