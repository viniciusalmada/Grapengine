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
CompType MaterialComponent::Type() const
{
  return CompType::MATERIAL;
}

MaterialComponent::MaterialComponent(Ptr<MaterialShader> s) : shader(std::move(s)) {}

CompType ColorOnlyComponent::Type() const
{
  return CompType::COLOR_ONLY;
}
ColorOnlyComponent::ColorOnlyComponent(Ptr<PosAndTex2DShader> s) : shader(std::move(s)) {}
ColorOnlyComponent::ColorOnlyComponent(const ColorOnlyComponent& other) :
    ColorOnlyComponent(other.shader)
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
NativeScriptComponent::NativeScriptComponent() :
    instance(nullptr), instantiateFun({}), destroyFun({})
{
}
CompType NativeScriptComponent::Type() const
{
  return CompType::NATIVE_SCRIPT;
}
