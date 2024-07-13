#include "ge_components.hpp"

using namespace GE;

//----------------------------------------------------------------------------------------------
TagComponent::TagComponent(std::string&& t) : m_tag(std::move(t)) {}

//----------------------------------------------------------------------------------------------
PrimitiveComponent::PrimitiveComponent(Ptr<Drawable> dra, Color c) :
    m_drawable(std::move(dra)), m_color(c)
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
AmbientLightComponent::AmbientLightComponent(Color c, f32 str) :
    m_color(c), m_strenght(str), m_active(true)
{
}

//----------------------------------------------------------------------------------------------
LightSourceComponent::LightSourceComponent(Color c, Vec3 pos, f32 str, bool act) :
    m_color(c), m_position(pos), m_strenght(str), m_active(act), m_drawable(Cube::Make())
{
}
