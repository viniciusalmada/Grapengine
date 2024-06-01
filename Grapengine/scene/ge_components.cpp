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

TagComponent::TagComponent(const char* t) : tag(t) {}
CompType TransformComponent::Type() const
{
  return CompType::TRANF;
}
TransformComponent::TransformComponent(const Mat4& transf) : transform(transf) {}
CompType TranslateScaleComponent::Type() const
{
  return CompType::TRANSL_SCALE;
}
TranslateScaleComponent::TranslateScaleComponent(const Vec3& pos, const Vec3& scale) :
    position_values(pos), scale_values(scale)
{
}
PrimitiveComponent::PrimitiveComponent(const Ptr<DrawingObject>& drawObj) : drawing_obj(drawObj) {}
CompType PrimitiveComponent::Type() const
{
  return CompType::PRIMITIVE;
}
PrimitiveComponent::PrimitiveComponent(const PrimitiveComponent& other) :
    PrimitiveComponent(other.drawing_obj)
{
}
CompType MaterialComponent::Type() const
{
  return CompType::MATERIAL;
}

MaterialComponent::MaterialComponent(Ptr<MaterialShader> s) : shader(s) {}

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

CompType CubeComponent::Type() const
{
  return CompType::CUBE;
}
CubeComponent::CubeComponent(Color color) : cube(color) {}
