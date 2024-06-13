#include "ge_components.hpp"

using namespace GE;

BaseComponent::~BaseComponent() = default;

CompType BaseComponent::Type() const
{
  return CompType::BASE;
}
CompType TagComponent::Type() const
{
  return CompType::TAG;
}

TagComponent::TagComponent(std::string&& t) : tag(std::move(t)) {}
CompType TransformComponent::Type() const
{
  return CompType::TRANF;
}
TransformComponent::TransformComponent(const Vec3& pos, const Vec3& scale, const Vec3& rot) :
    rotate_values(rot), position_values(pos), scale_values(scale)
{
}
PrimitiveComponent::PrimitiveComponent(Ptr<Drawable> dra, Color c) :
    drawable(std::move(dra)), color(c)
{
}

CompType PrimitiveComponent::Type() const
{
  return CompType::PRIMITIVE;
}

PrimitiveComponent::PrimitiveComponent(const PrimitiveComponent& other) :
    PrimitiveComponent(other.drawable, other.color)
{
}

CompType CameraComponent::Type() const
{
  return CompType::CAMERA;
}
CameraComponent::CameraComponent(const Vec3& eye, const Vec3& target, bool act, bool fixedRatio) :
    active(act), fixed_ratio(fixedRatio)
{
  camera.SetView(eye, target);
}
CameraComponent::CameraComponent() : CameraComponent(Vec3{ 5, 5, 5 }, Vec3{ 0, 0, 0 }, false, true)
{
}

NativeScriptComponent::NativeScriptComponent() :
    instance(nullptr), instantiateFun({}), destroyFun({})
{
}
CompType NativeScriptComponent::Type() const
{
  return CompType::NATIVE_SCRIPT;
}

AmbientLightComponent::~AmbientLightComponent() = default;

CompType AmbientLightComponent::Type() const
{
  return CompType::AMBIENT_LIGHT;
}

AmbientLightComponent::AmbientLightComponent(Color c, f32 str) :
    color(c), strenght(str), active(false)
{
}

LightSpotComponent::LightSpotComponent(Color c, Vec3 pos, f32 str, bool act) :
    color(c), position(pos), strenght(str), active(act), drawable(Cube::Make())
{
}
CompType LightSpotComponent::Type() const
{
  return CompType::LIGHT_SPOT;
}
LightSpotComponent::~LightSpotComponent() = default;
